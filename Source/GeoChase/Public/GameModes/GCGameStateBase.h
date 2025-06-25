// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

//
#include "GCGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBooleanChanged, bool, NewValue);

class AGCNpcCharacter;

USTRUCT(BlueprintType)
struct FGCLeaderboardData
{

    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadOnly)
    FName Name;

    UPROPERTY(BlueprintReadOnly)
    int32 Score;
};

UCLASS()
class GEOCHASE_API AGCGameStateBase : public AGameStateBase
{
    GENERATED_BODY()


public:
    AGCGameStateBase();

    UPROPERTY(BlueprintAssignable)
    FOnBooleanChanged OnCanDoActionChanged;

    UFUNCTION(BlueprintCallable)
    void TryAction(APlayerController* RequestingPlayer);

    UFUNCTION(BlueprintCallable)
    void ResetAction(AController* RequestingController);

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool GetCanDoAction() const { return bCanDoAction; }

    UFUNCTION(Server, Reliable, BlueprintCallable)
    void Server_UpdateLeaderboard(FName Name, int32 Score);

    UFUNCTION(BlueprintPure)
    FORCEINLINE TArray<FGCLeaderboardData>& GetLeaderboard() { return Leaderboard; }

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    virtual void Tick(float DeltaTime) override;

    virtual void BeginPlay() override;

private:
    UPROPERTY(ReplicatedUsing = OnRep_bCanDoAction)
    bool bCanDoAction = true;

    FTimerHandle ActionCooldownHandle;

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_MakeAction(APlayerController* RequestingPlayer);

    UPROPERTY(Replicated)
    TArray<FGCLeaderboardData> Leaderboard;

    void SetCanDoAction(const bool bCanDoAction);

    UFUNCTION()
    void OnRep_bCanDoAction(bool OldBCanDoAction);

};
