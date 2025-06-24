// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"

//
#include "GCPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;

USTRUCT(BlueprintType)
struct FEnhancedInputData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mapping context")
    UInputMappingContext* InputMapping = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* MoveAction = nullptr;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    UInputAction* LookAction = nullptr;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    UInputAction* SwitchAction = nullptr;

};

UCLASS()
class GEOCHASE_API AGCPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

protected:
    virtual void SetupInputComponent() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    FEnhancedInputData InputData;

private:
    void ControllerSetup();

    UFUNCTION()
    void Move(const FInputActionValue& Value);
    UFUNCTION()
    void Look(const FInputActionValue& Value);

};
