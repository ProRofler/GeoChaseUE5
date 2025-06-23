// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

//  
#include "GCPlayerCharacter.generated.h"

class AGCPlayerController;

UCLASS()
class GEOCHASE_API AGCPlayerCharacter : public ACharacter
{
    friend AGCPlayerController;

    GENERATED_BODY()

public:    // Sets default values for this character's properties
    AGCPlayerCharacter();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SK Player camera")
    TObjectPtr<class UCameraComponent> PlayerCamera;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
