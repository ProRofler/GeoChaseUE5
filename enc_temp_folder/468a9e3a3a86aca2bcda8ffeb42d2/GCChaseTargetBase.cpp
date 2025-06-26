// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GCChaseTargetBase.h"
#include "Components/SphereComponent.h"
#include "Characters/GCNpcCharacter.h"
#include "GameModes/GCGameStateBase.h"



AGCChaseTargetBase::AGCChaseTargetBase()
{
    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Object mesh");
    SetRootComponent(BaseMesh);

    BaseMesh->SetSimulatePhysics(true);
    BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BaseMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    BaseMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

    CollisionSphere = CreateDefaultSubobject<USphereComponent>("Sphere collision");
    CollisionSphere->SetupAttachment(BaseMesh);

    bReplicates = true;
    SetReplicateMovement(true);

    PrimaryActorTick.bCanEverTick = false;
}


void AGCChaseTargetBase::BeginPlay()
{
    Super::BeginPlay();

    if (CollisionSphere && BaseMesh) {
        CollisionSphere->SetSphereRadius(BaseMesh->GetStaticMesh()->GetBounds().BoxExtent.Size() * 1.5f);

        CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AGCChaseTargetBase::OnBeginOverlap);

    }

}

void AGCChaseTargetBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!HasAuthority()) return;

    if (auto GCGameState = GetWorld()->GetGameState<AGCGameStateBase>()) {

        if (auto Character = Cast<AGCNpcCharacter>(OtherActor)) {
            GCGameState->Server_UpdateLeaderboard(*GetNameSafe(Character), Score);
            GCGameState->ResetAction(Character->GetController());

            Destroy();
        }
    }
}


// Called every frame
void AGCChaseTargetBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

