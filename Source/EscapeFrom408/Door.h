// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractable.h"
#include "Door.generated.h"

UCLASS()
class ESCAPEFROM408_API ADoor : public AActor, public IIInteractable
{
	GENERATED_BODY()
	
public:
	virtual void OnFocused_Implementation() override;
	virtual void OnUnfocused_Implementation() override;
	virtual void Interact_Implementation() override;

	bool bIsPickedUp = false;

public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
