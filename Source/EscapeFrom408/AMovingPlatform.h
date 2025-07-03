#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "AMovingPlatform.generated.h"

UCLASS()
class ESCAPEFROM408_API AAMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    //// 컴포넌트
    //UPROPERTY(VisibleAnywhere)
    //UStaticMeshComponent* PlatformMesh;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* InteractionTrigger;

    // 이동 관련
    UPROPERTY(EditAnywhere)
    FVector TargetLocation;

    UPROPERTY(EditAnywhere)
    FVector StartLocation;

    UPROPERTY(EditAnywhere)
    float MoveSpeed = 200.0f;

    bool bShouldMove = false;

    void Interact();

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
    UStaticMeshComponent* Box;
};
