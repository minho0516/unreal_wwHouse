// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Kismet/GameplayStatics.h"
#include "EscapeFrom408Character.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ADoor::OnFocused_Implementation()
{
    if (APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0))
    {
        if (AEscapeFrom408Character* Character = Cast<AEscapeFrom408Character>(Pawn))
        {
            Character->ShowInteractUI();
        }
    }
}

void ADoor::OnUnfocused_Implementation()
{
    if (APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0))
    {
        if (AEscapeFrom408Character* Character = Cast<AEscapeFrom408Character>(Pawn))
        {
            Character->HideInteractUI();
        }
    }
}

void ADoor::Interact_Implementation()
{
    if (APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0))
    {
        if (AEscapeFrom408Character* Character = Cast<AEscapeFrom408Character>(Pawn))
        {
            if (Character->isRedKey)
            {
                UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
            }
        }
    }
}

