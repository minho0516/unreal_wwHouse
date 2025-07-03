// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROM408_API AAEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BTAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBlackboardData* BBAsset;
};
