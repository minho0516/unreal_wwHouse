// Fill out your copyright notice in the Description page of Project Settings.

#include "AEnemyCharacter.h"
#include "AEnemyAIController.h"

// Sets default values
AAEnemyCharacter::AAEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Perception 컴포넌트 생성
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	// 시야 설정
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = 1200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

	// 콜백 연결
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AAEnemyCharacter::OnTargetDetected);
}

// Called when the game starts or when spawned
void AAEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAEnemyCharacter::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	AAEnemyAIController* AICon = Cast<AAEnemyAIController>(GetController());
	if (AICon && AICon->GetBlackboardComponent())
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			// 감지 성공
			AICon->GetBlackboardComponent()->SetValueAsObject("TargetActor", Actor);
			AICon->GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", true);
		}
		else
		{
			// 시야에서 놓침
			AICon->GetBlackboardComponent()->SetValueAsObject("TargetActor", nullptr);
			AICon->GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", false);
		}
	}
}

void AAEnemyCharacter::HitDamage(int damage)
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy Hit! Current HP: %d, Damage Taken: %d"), hp, damage);

	Destroy();

	if (hp - damage <= 0) Destroy();
	else hp -= damage;
}


