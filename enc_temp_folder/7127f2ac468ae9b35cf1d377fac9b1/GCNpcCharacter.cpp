// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GCNpcCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

int32 AGCNpcCharacter::NpcCounter = 1;

AGCNpcCharacter::AGCNpcCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    bReplicates = true;
    SetReplicateMovement(true);

}

void AGCNpcCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGCNpcCharacter, NameID)
}

void AGCNpcCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority()) {

        if (GetWorld()) {
            NameID = FName(*FString::Printf(TEXT("NPC %d"), NpcCounter++));
        }
    }

}

void AGCNpcCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    --NpcCounter;
}

void AGCNpcCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}
