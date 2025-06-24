// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GCChaseTargetBase.h"


AGCChaseTargetBase::AGCChaseTargetBase()
{
    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Object mesh");
    SetRootComponent(BaseMesh);

    PrimaryActorTick.bCanEverTick = false;
}


void AGCChaseTargetBase::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AGCChaseTargetBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

