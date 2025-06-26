// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

//
#include "GCNpcCharacter.generated.h"

UCLASS()
class GEOCHASE_API AGCNpcCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AGCNpcCharacter();

    UPROPERTY(BlueprintReadOnly, Replicated)
    FName NameID;

    static int32 NpcCounter;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    virtual void Tick(float DeltaTime) override;

};
