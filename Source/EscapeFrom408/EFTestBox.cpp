#include "EFTestBox.h"
#include "EscapeFrom408Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEFTestBox::AEFTestBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	RootComponent = Box;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		BodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/_Art/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));
			if (BodyMeshRef.Object)
			{
				Box->SetStaticMesh(BodyMeshRef.Object);
			}
	Box->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
}

// Called when the game starts or when spawned
void AEFTestBox::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentHit.AddDynamic(this, &AEFTestBox::OnHit);
}

// Called every frame
void AEFTestBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEFTestBox::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Letsgooo"));
	AEscapeFrom408Character* Character = Cast<AEscapeFrom408Character>(OtherActor);
	if (Character != nullptr)
	{
		Character->IncreaseJumpPower();

		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, FName("ResetJump"), Character);

		GetWorld()->GetTimerManager().SetTimer(JumpResetTimerHandle, TimerDel, 3.0f, false);
	}
	Destroy();
}
void AEFTestBox::ResetJump(AEscapeFrom408Character* Character)
{
	Character->ResetJumpPower();
	UE_LOG(LogTemp, Warning, TEXT("JumpPower Reset hanguleFk"));
}
