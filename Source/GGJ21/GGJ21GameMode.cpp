// Copyright Epic Games, Inc. All Rights Reserved.

#include "GGJ21GameMode.h"
#include "GGJ21HUD.h"
#include "GGJ21Character.h"
#include "UObject/ConstructorHelpers.h"

AGGJ21GameMode::AGGJ21GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGGJ21HUD::StaticClass();
}
