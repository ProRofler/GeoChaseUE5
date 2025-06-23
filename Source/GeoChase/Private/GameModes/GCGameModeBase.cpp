// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GCGameModeBase.h"
#include "Player/GCPlayerController.h"
#include "Player/GCPlayerCharacter.h"


AGCGameModeBase::AGCGameModeBase()
{
    //
    DefaultPawnClass = AGCPlayerCharacter::StaticClass();
    PlayerControllerClass = AGCPlayerController::StaticClass();
}
