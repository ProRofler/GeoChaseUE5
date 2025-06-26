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

bool AGCGameStateBase::DoesHaveLeader() const
{

    if (Leaderboard.IsEmpty() || Leaderboard.Num() < 2) return false;

    return Leaderboard[0].Score > Leaderboard[1].Score;

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

AActor* AGCGameStateBase::FindFurthestActor(FVector Origin, const TArray<AActor*>& ActorsToCheck)
{
    AActor* FurthestActor = nullptr;
    float DistanceFromNearestActor = TNumericLimits<float>::Min();

    for (AActor* ActorToCheck : ActorsToCheck)
    {
        if (ActorToCheck)
        {
            const float DistanceFromActorToCheck = (Origin - ActorToCheck->GetActorLocation()).SizeSquared();
            if (DistanceFromActorToCheck > DistanceFromNearestActor)
            {
                FurthestActor = ActorToCheck;
                DistanceFromNearestActor = DistanceFromActorToCheck;
            }
        }
    }

    return FurthestActor;
}

void AGCGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGCGameStateBase, bCanDoAction);
    DOREPLIFETIME(AGCGameStateBase, Leaderboard);
    DOREPLIFETIME(AGCGameStateBase, MatchTime);
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
                FName NPCName = Cast<AGCNpcCharacter>(NPC) ? Cast<AGCNpcCharacter>(NPC)->NameID : "Error";

                data.Name = NPCName;
                data.Score = 0;

                Leaderboard.Add(data);
            }

        }

        // Start session timer
        GetWorldTimerManager().SetTimer(MatchTimerHandle, [this]()
            {
                if (MatchTime > 0.f)
                {
                    MatchTime -= 1.f;
                    UE_LOG(LogTemp, Log, TEXT("MatchTime: %f"), MatchTime);
                }
                else
                {
                    GetWorldTimerManager().ClearTimer(MatchTimerHandle);
                    SetCanDoAction(false);

                    if (OnSessionEnded.IsBound())
                    {
                        OnSessionEnded.Broadcast();
                    }

                    UE_LOG(LogTemp, Log, TEXT("Match finished"));
                }
            }, 1.f, true);


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

