// Fill out your copyright notice in the Description page of Project Settings.


#include "BGMPlayer.h"

// Sets default values
ABGMPlayer::ABGMPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->bIsUISound = false;
	AudioComponent->bAllowSpatialization = false;
	//AudioComponent->SetupAttachment(this);

}

// Called when the game starts or when spawned
void ABGMPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	if (AudioComponent && BGMClip)
	{
		AudioComponent->SetSound(BGMClip);
	}
}

// Called every frame
void ABGMPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

