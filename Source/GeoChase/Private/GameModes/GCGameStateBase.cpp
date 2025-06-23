// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GCGameStateBase.h"


void AGCGameStateBase::Multicast_MakeAction_Implementation(APlayerController* RequestingPlayer)
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

void AGCGameStateBase::Server_TryAction_Implementation(APlayerController* RequestingPlayer)
{

    if (!bCanDoAction) {
        if (GEngine) {
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Wait for cooldown!"));
        }
        return;
    }

    bCanDoAction = false;

    Multicast_MakeAction(RequestingPlayer);

    GetWorldTimerManager().SetTimer(ActionCooldownHandle, //
        FTimerDelegate::CreateLambda([&]()
            {
                bCanDoAction = true;
            }), // 
        2.0f, // 
        false);


}

