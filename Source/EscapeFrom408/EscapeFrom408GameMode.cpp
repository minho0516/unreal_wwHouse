// Copyright Epic Games, Inc. All Rights Reserved.

#include "EscapeFrom408GameMode.h"
#include "EscapeFrom408Character.h"
#include "UObject/ConstructorHelpers.h"

AEscapeFrom408GameMode::AEscapeFrom408GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
