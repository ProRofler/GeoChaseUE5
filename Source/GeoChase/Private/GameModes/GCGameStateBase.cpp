// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GCGameStateBase.h"
#include "Player/GCPlayerCharacter.h"

#include "Net/UnrealNetwork.h"



AGCGameStateBase::AGCGameStateBase()
{
    bReplicates = true;
    NetUpdateFrequency = 100.f;
}


void AGCGameStateBase::Multicast_MakeAction_Implementation(APlayerController* RequestingPlayer)
{

    if (RequestingPlayer && GEngine && RequestingPlayer->IsLocalController()) {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("%s action!"), *RequestingPlayer->GetCharacter()->GetName()));

        if (auto PlayerCharacter = Cast<AGCPlayerCharacter>(RequestingPlayer->GetCharacter()))
        {
            PlayerCharacter->Server_DoAction();
        }
    }

}

void AGCGameStateBase::TryAction(APlayerController* RequestingPlayer)
{

    if (!bCanDoAction) {
        if (GEngine && RequestingPlayer && RequestingPlayer->IsLocalController()) {
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("%s wait for cooldown!"), *RequestingPlayer->GetCharacter()->GetName()));

        }
        return;
    }

    SetCanDoAction(false);

    Multicast_MakeAction(RequestingPlayer);

    GetWorldTimerManager().SetTimer(ActionCooldownHandle, //
        FTimerDelegate::CreateLambda([&]()
            {
                SetCanDoAction(true);
            }), // 
        5.0f, // 
        false);


}

void AGCGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGCGameStateBase, bCanDoAction);
}

void AGCGameStateBase::Tick(float DeltaTime)
{
    if (GEngine) {
        GEngine->AddOnScreenDebugMessage(25, 2.f, FColor::Green, FString::Printf(TEXT("Can do action -- %b"), bCanDoAction));
    }

}

void AGCGameStateBase::SetCanDoAction(const bool CanDoAction)
{

    bCanDoAction = CanDoAction;

    if (OnCanDoActionChanged.IsBound())
    {
        OnCanDoActionChanged.Broadcast(bCanDoAction);
    }


}

void AGCGameStateBase::OnRep_bCanDoAction(bool OldBCanDoAction)
{
    if (OnCanDoActionChanged.IsBound())
    {
        OnCanDoActionChanged.Broadcast(bCanDoAction);
    }
}

