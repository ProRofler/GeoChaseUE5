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

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

};
