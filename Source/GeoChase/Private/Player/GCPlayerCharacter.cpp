// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GCPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Gameplay/GCChaseTargetBase.h"
#include "GameModes/GCGameStateBase.h"




AGCPlayerCharacter::AGCPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Player camera");
    PlayerCamera->SetupAttachment(GetRootComponent());
    PlayerCamera->bUsePawnControlRotation = true;

    GetMesh()->SetOwnerNoSee(true);
}

void AGCPlayerCharacter::Server_DoAction_Implementation()
{
    LaunchCharacter(GetActorForwardVector() * 5000, false, false);
}

PRAGMA_ENABLE_OPTIMIZATION
void AGCPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (!GetWorld() || !ChaseTargetClass) return;

    if (auto GCGameState = GetWorld()->GetGameState<AGCGameStateBase>()) {

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        SpawnParams.Owner = this;



        auto ChaseTarget = GetWorld()->SpawnActor<AGCChaseTargetBase>(ChaseTargetClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

        if (ChaseTarget)
        {
            ChaseTarget->SetActorEnableCollision(false);
            ChaseTarget->GetBaseMesh()->SetOnlyOwnerSee(true);

            ChaseTarget->AttachToComponent(PlayerCamera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
            ChaseTarget->SetActorRelativeLocation(FVector(30.f, 10.f, -10.f));
        }

        GCGameState->GetCanDoAction() ? ChaseTarget->GetRootComponent()->SetVisibility(true) : ChaseTarget->GetRootComponent()->SetVisibility(false);
    }

}
PRAGMA_DISABLE_OPTIMIZATION

void AGCPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AGCPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}


