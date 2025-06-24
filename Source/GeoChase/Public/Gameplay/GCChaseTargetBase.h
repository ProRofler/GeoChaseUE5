// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

//
#include "GCChaseTargetBase.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class GEOCHASE_API AGCChaseTargetBase : public AActor
{
    GENERATED_BODY()

public:
    AGCChaseTargetBase();

    UFUNCTION(BlueprintPure)
    FORCEINLINE UStaticMeshComponent* GetBaseMesh() const { return BaseMesh; }

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "GC Chase target settings")
    TObjectPtr<UStaticMeshComponent> BaseMesh;

    TObjectPtr<USphereComponent> CollisionSphere;

private:
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex);

};
