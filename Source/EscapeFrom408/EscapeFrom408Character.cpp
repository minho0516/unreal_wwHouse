// Copyright Epic Games, Inc. All Rights Reserved.

#include "EscapeFrom408Character.h"
#include "EscapeFrom408Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "AEnemyCharacter.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "IInteractable.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AEscapeFrom408Character

AEscapeFrom408Character::AEscapeFrom408Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	// 기존 Mesh1P 등은 이미 설정돼있다고 가정

	// Crowbar 생성
	CrowbarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrowbarMesh"));
	CrowbarMesh->SetupAttachment(Mesh1P, "weaponSocket"); // 손 소켓에 붙이기

	/*
	// 기본 위치 조정 (손에 잘 맞게)
	CrowbarMesh->SetRelativeLocation(FVector(-49.0f, -17.0f, 91.0f)); // 위치는 너가 조정 필요
	CrowbarMesh->SetRelativeRotation(FRotator(22.0f, 67.0f, 159.0f));
	CrowbarMesh->SetRelativeScale3D(FVector(1.0f));
	*/

	// 충돌 비활성화 (무기 피킹 중 충돌 방지)
	CrowbarMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEscapeFrom408Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = 250.0f;

	if (CrosshairWidgetClass)
	{
		UUserWidget* CrosshairWidget = CreateWidget<UUserWidget>(GetWorld(), CrosshairWidgetClass);
		if (CrosshairWidget)
		{
			CrosshairWidget->AddToViewport();
		}
	}

	originJumpPower = GetCharacterMovement()->JumpZVelocity;

	if (InteractWidgetClass)
	{
		InteractWidget = CreateWidget<UUserWidget>(GetWorld(), InteractWidgetClass);
		if (InteractWidget)
		{
			InteractWidget->AddToViewport();
			InteractWidget->SetVisibility(ESlateVisibility::Hidden); // 처음엔 숨김
		}
	}

}

void AEscapeFrom408Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + FirstPersonCameraComponent->GetForwardVector() * 400.0f;

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility))
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor != FocusedActor)
		{
			if (FocusedActor && FocusedActor->Implements<UIInteractable>())
				IIInteractable::Execute_OnUnfocused(FocusedActor);

			FocusedActor = HitActor;

			if (FocusedActor && FocusedActor->Implements<UIInteractable>())
				IIInteractable::Execute_OnFocused(FocusedActor);
		}
	}
	else if (FocusedActor)
	{
		if (FocusedActor->Implements<UIInteractable>())
			IIInteractable::Execute_OnUnfocused(FocusedActor);
		FocusedActor = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AEscapeFrom408Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEscapeFrom408Character::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEscapeFrom408Character::Look);

		// Attacking
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AEscapeFrom408Character::Attack);

		// Interactive
		EnhancedInputComponent->BindAction(InteracAction, ETriggerEvent::Triggered, this, &AEscapeFrom408Character::Interactive);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AEscapeFrom408Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AEscapeFrom408Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AEscapeFrom408Character::Attack()
{
	if (bIsGunEquipped) return;

	UE_LOG(LogTemp, Warning, TEXT("Crowbar Swing!"));



	// 간단한 공격 판정 (라인 트레이스)
	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + FirstPersonCameraComponent->GetForwardVector() * 400.f;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	//if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn ,Params))
	//{
	//	//AActor* HitActor = Hit.GetActor();
	//	//if (HitActor)
	//	//{
	//	//	UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitActor->GetName());
	//	//	Cast<AAEnemyCharacter>(HitActor)->HitDamage(30); // 적에게 30 데미지 주기
	//	//}
	//}

	if (CrowbarSwingMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("IF CROWBARSWINGMONTAGE"));
		UAnimInstance* AnimInst = Mesh1P->GetAnimInstance();
		if (AnimInst)
		{
			float PlayResult = AnimInst->Montage_Play(CrowbarSwingMontage);
			UE_LOG(LogTemp, Warning, TEXT("Montage Played: %f"), PlayResult);
		}
	}


	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 2.0f);
}

void AEscapeFrom408Character::EquipGun()
{
	UE_LOG(LogTemp, Warning, TEXT("Player::EquipGun Called"));
	if (EquipGunMontage)
	{
		UAnimInstance* AnimInst = Mesh1P->GetAnimInstance();
		if (AnimInst)
		{
			float Result = AnimInst->Montage_Play(EquipGunMontage);
			UE_LOG(LogTemp, Warning, TEXT("EquipGun Montage Played: %f"), Result);
		}
	}

	bIsGunEquipped = true;

	// 메시가 있다면 활성화
	// GunMesh->SetHiddenInGame(false);
}

void AEscapeFrom408Character::IncreaseJumpPower()
{
	GetCharacterMovement()->JumpZVelocity = originJumpPower * 1.5f;
}

void AEscapeFrom408Character::ResetJumpPower()
{
	GetCharacterMovement()->JumpZVelocity = originJumpPower;
}

void AEscapeFrom408Character::Interactive()
{
	
	if (FocusedActor && FocusedActor->Implements<UIInteractable>())
		IIInteractable::Execute_Interact(FocusedActor);
}

void AEscapeFrom408Character::ShowInteractUI()
{
	if (InteractWidget)
	{
		InteractWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AEscapeFrom408Character::HideInteractUI()
{
	if (InteractWidget)
	{
		InteractWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
