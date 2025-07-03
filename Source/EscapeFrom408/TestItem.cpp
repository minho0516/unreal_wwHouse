// Fill out your copyright notice in the Description page of Project Settings.

#include "TestItem.h"
#include "Kismet/GameplayStatics.h"
#include "EscapeFrom408Character.h"

// Sets default values
ATestItem::ATestItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestItem::OnFocused_Implementation()
{
    if (APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0))
    {
        if (AEscapeFrom408Character* Character = Cast<AEscapeFrom408Character>(Pawn))
        {
            Character->ShowInteractUI();
        }
    }
}

void ATestItem::OnUnfocused_Implementation()
{
    if (APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0))
    {
        if (AEscapeFrom408Character* Character = Cast<AEscapeFrom408Character>(Pawn))
        {
            Character->HideInteractUI();
        }
    }
}

void ATestItem::Interact_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("NBLUE"));

    if (APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0))
    {
        if (AEscapeFrom408Character* Character = Cast<AEscapeFrom408Character>(Pawn))
        {
            Character->isRedKey = true;
        }
    }

    bIsPickedUp = true;
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
}