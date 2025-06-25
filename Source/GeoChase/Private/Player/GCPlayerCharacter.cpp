// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GCPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Gameplay/GCChaseTargetBase.h"
#include "GameModes/GCGameStateBase.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"




AGCPlayerCharacter::AGCPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    bReplicates = true;

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
    if (GetWorld() && ChaseTargetClasses[CurrentChaseTargetClassIndex]) {

        FTransform SpawnTransform;
        SpawnTransform.SetLocation(PlayerCamera->GetComponentLocation() + PlayerCamera->GetForwardVector() * 50.f);


        AGCChaseTargetBase* SpawnedChaseTarget = GetWorld()->SpawnActorDeferred<AGCChaseTargetBase>(ChaseTargetClasses[CurrentChaseTargetClassIndex].Get(), SpawnTransform);

        if (SpawnedChaseTarget) {
            SpawnedChaseTarget->GetBaseMesh()->AddImpulse(PlayerCamera->GetForwardVector() * 1000.f);
            SpawnedChaseTarget->FinishSpawning(SpawnTransform);
        }
    }
}

void AGCPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    UpdateChaseTargetMesh();

    if (auto GCGameState = GetWorld()->GetGameState<AGCGameStateBase>()) {
        GCGameState->OnCanDoActionChanged.AddDynamic(this, &ThisClass::HandleChaseTargetMeshVisibility);
        GCGameState->GetCanDoAction() ? ChaseTargetMesh->SetVisibility(true) : ChaseTargetMesh->SetVisibility(false);
    }
}

void AGCPlayerCharacter::HandleChaseTargetMeshVisibility(const bool NewVisibility)
{
    ChaseTargetMesh->SetVisibility(NewVisibility);
}

void AGCPlayerCharacter::NextChaseTarget_Implementation()
{
    if (!GetWorld() || ChaseTargetClasses.IsEmpty()) return;

    CurrentChaseTargetClassIndex = ++CurrentChaseTargetClassIndex % ChaseTargetClasses.Num();

    UpdateChaseTargetMesh();

}

void AGCPlayerCharacter::UpdateChaseTargetMesh()
{
    if (!GetWorld() || ChaseTargetClasses.IsEmpty()) return;

    if (auto ChaseTargetMeshComponent = ChaseTargetClasses[CurrentChaseTargetClassIndex]->GetDefaultObject<AGCChaseTargetBase>()->GetBaseMesh())
    {
        ChaseTargetMesh->SetStaticMesh(ChaseTargetMeshComponent->GetStaticMesh());
        ChaseTargetMesh->SetRelativeScale3D(FVector(ChaseTargetMeshComponent->GetRelativeScale3D()));
    }
}

void AGCPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AGCPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGCPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGCPlayerCharacter, CurrentChaseTargetClassIndex);
}


