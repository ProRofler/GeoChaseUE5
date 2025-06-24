// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GCChaseTargetBase.h"
#include "Components/SphereComponent.h"
#include "Player/GCPlayerCharacter.h"



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
        CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AGCChaseTargetBase::OnOverlapEnd);

    }

}

void AGCChaseTargetBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (Cast<AGCPlayerCharacter>(OtherActor)) {
        UE_LOG(LogTemp, Warning, TEXT("Overlapping!"));
    }
}

void AGCChaseTargetBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (Cast<AGCPlayerCharacter>(OtherActor)) {
        UE_LOG(LogTemp, Warning, TEXT("END Overlapping!"));
    }
}

// Called every frame
void AGCChaseTargetBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

