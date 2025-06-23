// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GCPlayerCharacter.h"
#include "Camera/CameraComponent.h"



AGCPlayerCharacter::AGCPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Player camera");
    PlayerCamera->SetupAttachment(GetRootComponent());
    PlayerCamera->bUsePawnControlRotation = true;
}

void AGCPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AGCPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AGCPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}


