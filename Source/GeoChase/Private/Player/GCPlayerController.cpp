// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GCPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Player/GCPlayerCharacter.h"

void AGCPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void AGCPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    ControllerSetup();

    if (auto Input = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        Input->BindAction(InputData.MoveAction, ETriggerEvent::Triggered, this,
            &AGCPlayerController::Move);
        Input->BindAction(InputData.LookAction, ETriggerEvent::Triggered, this,
            &AGCPlayerController::Look);
    }
}


void AGCPlayerController::ControllerSetup()
{
    if (auto PC = Cast<APlayerController>(this))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->ClearAllMappings();
            Subsystem->AddMappingContext(InputData.InputMapping, 0);
        }
    }
}

void AGCPlayerController::Move(const FInputActionValue& Value)
{
    if (Value.IsNonZero() && GetPawn())
    {
        const FVector2D MovingAxis = Value.Get<FVector2D>();

        GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), MovingAxis.X);
        GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), MovingAxis.Y);
    }
}

void AGCPlayerController::Look(const FInputActionValue& Value)
{
    if (Value.IsNonZero() && GetPawn())
    {
        const auto LookingAxisX = Value.Get<FVector2D>().X;
        const auto LookingAxisY = Value.Get<FVector2D>().Y * -1;

        GetPawn()->AddControllerYawInput(LookingAxisX);
        GetPawn()->AddControllerPitchInput(LookingAxisY);

    }
}

