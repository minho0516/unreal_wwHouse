#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "BGMPlayer.generated.h"

UCLASS()
class ESCAPEFROM408_API ABGMPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABGMPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "BGM")
	USoundBase* BGMClip;


	UPROPERTY()
	UAudioComponent* AudioComponent;
};
