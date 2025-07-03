// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EFTestBox.generated.h"

UCLASS()
class ESCAPEFROM408_API AEFTestBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEFTestBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent*
		OtherComp, FVector NormalImpulse, const FHitResult& Hit);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> Box;

public:
	FTimerHandle JumpResetTimerHandle;

	UFUNCTION()
	void ResetJump(AEscapeFrom408Character* Character);
};
