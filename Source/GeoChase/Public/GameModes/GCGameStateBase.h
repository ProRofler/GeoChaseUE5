// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GCGameStateBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBooleanChanged, bool)

UCLASS()
class GEOCHASE_API AGCGameStateBase : public AGameStateBase
{
    GENERATED_BODY()


public:
    AGCGameStateBase();

    FOnBooleanChanged OnCanDoActionChanged;

    UFUNCTION(BlueprintCallable)
    void TryAction(APlayerController* RequestingPlayer);

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool GetCanDoAction() const { return bCanDoAction; }


    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    virtual void Tick(float DeltaTime) override;


private:
    UPROPERTY(ReplicatedUsing = OnRep_bCanDoAction)
    bool bCanDoAction = true;

    FTimerHandle ActionCooldownHandle;

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_MakeAction(APlayerController* RequestingPlayer);


    void SetCanDoAction(const bool bCanDoAction);

    UFUNCTION()
    void OnRep_bCanDoAction(bool OldBCanDoAction);



};
