// Fill out your copyright notice in the Description page of Project Settings.


#include "AEnemyAIController.h"

void AAEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		RunBehaviorTree(BTAsset);
	}
}

