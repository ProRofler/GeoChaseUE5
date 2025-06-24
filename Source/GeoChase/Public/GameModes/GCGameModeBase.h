// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

//
#include "GCGameModeBase.generated.h"

USTRUCT()
struct FGCChaseTargetData {
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = "Chase target")
    UStaticMesh* ChaseMesh;

    UPROPERTY(EditDefaultsOnly, Category = "Chase target")
    int32 Score = 3;
};

UCLASS()
class GEOCHASE_API AGCGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    AGCGameModeBase();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "GC Game Settings")
    TArray<FGCChaseTargetData> ChaseTargetData;

};
