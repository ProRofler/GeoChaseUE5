// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GCGameModeBase.h"


void AGCGameModeBase::ResetCooldown()
{
    bCanDoAction = true;
}

void AGCGameModeBase::Multicast_MakeAction_Implementation()
{
    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        if (APlayerController* PC = Iterator->Get())
        {
            if (APawn* Pawn = PC->GetPawn())
            {
                if (GEngine) {
                    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Action!"));
                }
            }
        }
    }
}

void AGCGameModeBase::Server_TryAction_Implementation(APlayerController* RequestingPlayer)
{

    if (!bCanDoAction) {
        if (GEngine) {
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Wait for cooldown!"));
        }
        return;
    }

    bCanDoAction = false;

    Multicast_MakeAction();

    GetWorldTimerManager().SetTimer(ActionCooldownHandle, this, &AGCGameModeBase::ResetCooldown, 2.0f, false);

}