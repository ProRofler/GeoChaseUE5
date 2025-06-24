// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GCPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Gameplay/GCChaseTargetBase.h"
#include "GameModes/GCGameStateBase.h"
#include "Components/StaticMeshComponent.h"



AGCPlayerCharacter::AGCPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Player camera");
    PlayerCamera->SetupAttachment(GetRootComponent());
    PlayerCamera->bUsePawnControlRotation = true;

    GetMesh()->SetOwnerNoSee(true);

    ChaseTargetMesh = CreateDefaultSubobject<UStaticMeshComponent>("Chase mesh component");
    ChaseTargetMesh->SetupAttachment(PlayerCamera);
    //ChaseTargetMesh->AttachToComponent(PlayerCamera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    ChaseTargetMesh->SetRelativeLocation(FVector(30.f, 10.f, -10.f));
    ChaseTargetMesh->SetOnlyOwnerSee(true);
    ChaseTargetMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void AGCPlayerCharacter::Server_DoAction_Implementation()
{
    if (GetWorld() && ChaseTargetClass) {

        FTransform SpawnTransform;
        SpawnTransform.SetLocation(PlayerCamera->GetComponentLocation() + PlayerCamera->GetForwardVector() * 50.f);


        AGCChaseTargetBase* SpawnedChaseTarget = GetWorld()->SpawnActorDeferred<AGCChaseTargetBase>(ChaseTargetClass.Get(), SpawnTransform);

        if (SpawnedChaseTarget) {
            SpawnedChaseTarget->GetBaseMesh()->AddImpulse(PlayerCamera->GetForwardVector() * 1000.f);
            SpawnedChaseTarget->FinishSpawning(SpawnTransform);

            //
            FTimerHandle DestroyTimerHandle;
            GetWorldTimerManager().SetTimer(DestroyTimerHandle, //
                FTimerDelegate::CreateLambda([SpawnedChaseTarget]()
                    {
                        SpawnedChaseTarget->Destroy();
                    }), // 
                3.0f, // 
                false);

        }



    }
}

void AGCPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (!GetWorld() || !ChaseTargetClass) return;

    if (auto GCGameState = GetWorld()->GetGameState<AGCGameStateBase>()) {

        GCGameState->OnCanDoActionChanged.AddDynamic(this, &ThisClass::HandleChaseTargetMeshVisibility);

        if (auto ChaseTargetMeshComponent = ChaseTargetClass->GetDefaultObject<AGCChaseTargetBase>()->GetBaseMesh())
        {
            ChaseTargetMesh->SetStaticMesh(ChaseTargetMeshComponent->GetStaticMesh());
            ChaseTargetMesh->SetRelativeScale3D(FVector(ChaseTargetMeshComponent->GetRelativeScale3D()));

        }

        GCGameState->GetCanDoAction() ? ChaseTargetMesh->SetVisibility(true) : ChaseTargetMesh->SetVisibility(false);
    }

}

void AGCPlayerCharacter::HandleChaseTargetMeshVisibility(const bool NewVisibility)
{
    ChaseTargetMesh->SetVisibility(NewVisibility);
}

void AGCPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AGCPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}


