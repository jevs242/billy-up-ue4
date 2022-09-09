// Copyright Epic Games, Inc. All Rights Reserved.

#include "CubeUpGameMode.h"
#include "CubeUpCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACubeUpGameMode::ACubeUpGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
