// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GCGameStateBase.h"
#include "Player/GCPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/GCNpcCharacter.h"

#include "Net/UnrealNetwork.h"

#include "Algo/Sort.h"



AGCGameStateBase::AGCGameStateBase()
{
    bReplicates = true;
    NetUpdateFrequency = 10.f;
}


void AGCGameStateBase::Multicast_MakeAction_Implementation(APlayerController* RequestingPlayer)
{

    if (RequestingPlayer && GEngine && RequestingPlayer->IsLocalController()) {
        //GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("%s action!"), *RequestingPlayer->GetCharacter()->GetName()));

        if (auto PlayerCharacter = Cast<AGCPlayerCharacter>(RequestingPlayer->GetCharacter()))
        {
            PlayerCharacter->Server_DoAction();
        }
    }

}

void AGCGameStateBase::TryAction(APlayerController* RequestingPlayer)
{

    if (!bCanDoAction) {
        /*if (GEngine && RequestingPlayer && RequestingPlayer->IsLocalController()) {
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("%s wait for cooldown!"), *RequestingPlayer->GetCharacter()->GetName()));

        }*/
        return;
    }

    SetCanDoAction(false);

    Multicast_MakeAction(RequestingPlayer);

}

void AGCGameStateBase::ResetAction(AController* RequestingController)
{
    if (bCanDoAction) return;

    SetCanDoAction(true);
}

void AGCGameStateBase::Server_UpdateLeaderboard_Implementation(FName Name, int32 Score)
{
    if (Leaderboard.IsEmpty()) return;

    for (auto& data : Leaderboard)
    {
        if (data.Name == Name) {
            data.Score += Score;
            break;
        }
    }
    SortLeaderboard();
}

void AGCGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGCGameStateBase, bCanDoAction);
    DOREPLIFETIME(AGCGameStateBase, Leaderboard);
}

void AGCGameStateBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    /*if (GEngine) {
        GEngine->AddOnScreenDebugMessage(25, 2.f, FColor::Green, FString::Printf(TEXT("Can do action -- %b"), bCanDoAction));
    }*/

}

void AGCGameStateBase::BeginPlay()
{

    Super::BeginPlay();

    if (HasAuthority() && GetWorld()) {

        TArray<AActor*> FoundNPC;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGCNpcCharacter::StaticClass(), FoundNPC);

        if (!FoundNPC.IsEmpty())
        {
            for (auto& NPC : FoundNPC)
            {
                FGCLeaderboardData data;
                data.Name = *GetNameSafe(NPC);
                data.Score = 0;

                Leaderboard.Add(data);
            }

        }

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

void AGCGameStateBase::SortLeaderboard()
{
    Algo::Sort(Leaderboard, [](const FGCLeaderboardData& A, const FGCLeaderboardData& B)
        {
            return A.Score > B.Score;
        });
}

void AGCGameStateBase::OnRep_bCanDoAction(bool OldBCanDoAction)
{
    if (OnCanDoActionChanged.IsBound())
    {
        OnCanDoActionChanged.Broadcast(bCanDoAction);
    }
}

