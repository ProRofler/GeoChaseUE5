// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

//  
#include "GCPlayerCharacter.generated.h"

class AGCPlayerController;
class AGCChaseTargetBase;

UCLASS()
class GEOCHASE_API AGCPlayerCharacter : public ACharacter
{
    friend AGCPlayerController;

    GENERATED_BODY()

public:    // Sets default values for this character's properties
    AGCPlayerCharacter();

    UFUNCTION(Server, Reliable, BlueprintCallable)
    void Server_DoAction();

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GC Player camera")
    TObjectPtr<class UCameraComponent> PlayerCamera;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GC Chase target")
    TSubclassOf<AGCChaseTargetBase> ChaseTargetClass;

private:
    UPROPERTY()
    TObjectPtr<class UStaticMeshComponent> ChaseTargetMesh;


};
