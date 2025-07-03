#include "AMovingPlatform.h"

// Sets default values
AAMovingPlatform::AAMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // �޽� ������Ʈ ����
    //Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
}

// Called when the game starts or when spawned
void AAMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bShouldMove)
    {
        FVector CurrentLocation = GetActorLocation();
        FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
        SetActorLocation(NewLocation);

        // ���� ����
        if (FVector::Dist(NewLocation, TargetLocation) < 1.0f)
        {
            bShouldMove = false;
        }
    }
}

void AAMovingPlatform::Interact()
{
    if (!bShouldMove)
    {
        bShouldMove = true;
    }
}

