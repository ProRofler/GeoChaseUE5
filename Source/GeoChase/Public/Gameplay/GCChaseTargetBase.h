// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

//
#include "GCChaseTargetBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class GEOCHASE_API AGCChaseTargetBase : public AActor
{
    GENERATED_BODY()

public:
    AGCChaseTargetBase();

    UFUNCTION(BlueprintPure)
    FORCEINLINE UStaticMeshComponent* GetBaseMesh() const { return BaseMesh; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GC Chase target settings")
    TObjectPtr<UStaticMeshComponent> BaseMesh;


public:
    virtual void Tick(float DeltaTime) override;

};
