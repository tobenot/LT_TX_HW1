// Copyright Epic Games, Inc. All Rights Reserved.

#include "RT_Hwork1CPPGameMode.h"
#include "RT_Hwork1CPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ART_Hwork1CPPGameMode::ART_Hwork1CPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}
