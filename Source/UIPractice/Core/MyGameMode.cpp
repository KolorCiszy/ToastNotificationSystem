// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "MyGameState.h"
#include "MyPlayerController.h"

AMyGameMode::AMyGameMode()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
	GameStateClass = AMyGameState::StaticClass();
}
