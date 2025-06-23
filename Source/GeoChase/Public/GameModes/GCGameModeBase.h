// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

//
#include "GCGameModeBase.generated.h"


UCLASS()
class GEOCHASE_API AGCGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Reliable, Server)
    void Server_TryAction(APlayerController* RequestingPlayer);

protected:
    bool bCanDoAction = true;
    FTimerHandle ActionCooldownHandle;

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_MakeAction();

    void ResetCooldown();


};
