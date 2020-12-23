// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjetMondeVirtuelGameMode.h"
#include "ProjetMondeVirtuelPlayerController.h"
#include "ProjetMondeVirtuelCharacter.h"
#include "UObject/ConstructorHelpers.h"


AProjetMondeVirtuelGameMode::AProjetMondeVirtuelGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProjetMondeVirtuelPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}