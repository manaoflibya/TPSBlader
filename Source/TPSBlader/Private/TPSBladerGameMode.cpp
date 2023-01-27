// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPSBladerGameMode.h"
#include "TPSBladerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATPSBladerGameMode::ATPSBladerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
