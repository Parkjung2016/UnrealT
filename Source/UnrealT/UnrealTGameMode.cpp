// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealTGameMode.h"
#include "UnrealTCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealTGameMode::AUnrealTGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
