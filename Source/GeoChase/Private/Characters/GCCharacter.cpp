// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GCCharacter.h"


// Sets default values
AGCCharacter::AGCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

