// Copyright Epic Games, Inc. All Rights Reserved.


#include "MainGameMode.h"
#include "PingPong/Controllers/MainPlayerController.h"
#include "GameFramework/GameStateBase.h"

AMainGameMode::AMainGameMode()
{
	PlayerControllerClass = AMainPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_PlayerPlatform"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}