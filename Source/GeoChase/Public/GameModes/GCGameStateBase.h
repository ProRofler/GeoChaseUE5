// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GCGameStateBase.generated.h"


UCLASS()
class GEOCHASE_API AGCGameStateBase : public AGameStateBase
{
    GENERATED_BODY()


public:
    UFUNCTION(BlueprintCallable, Reliable, Server)
    void Server_TryAction(APlayerController* RequestingPlayer);

protected:
    bool bCanDoAction = true;
    FTimerHandle ActionCooldownHandle;

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_MakeAction(APlayerController* RequestingPlayer);

};
