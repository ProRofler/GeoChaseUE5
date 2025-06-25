// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GCNpcCharacter.h"


AGCNpcCharacter::AGCNpcCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    bReplicates = true;
    SetReplicateMovement(true);

}

void AGCNpcCharacter::BeginPlay()
{
    Super::BeginPlay();

}

void AGCNpcCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}
