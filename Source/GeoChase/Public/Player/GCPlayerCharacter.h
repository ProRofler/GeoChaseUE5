// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/GCPlayerInterface.h"


//  
#include "GCPlayerCharacter.generated.h"

class AGCPlayerController;
class AGCChaseTargetBase;

UCLASS()
class GEOCHASE_API AGCPlayerCharacter : public ACharacter, public IGCPlayerInterface
{
    friend AGCPlayerController;

    GENERATED_BODY()

public:
    AGCPlayerCharacter();

    UFUNCTION(Server, Reliable, BlueprintCallable)
    void Server_DoAction();

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GC Player camera")
    TObjectPtr<class UCameraComponent> PlayerCamera;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GC Chase target")
    TArray<TSubclassOf<AGCChaseTargetBase>> ChaseTargetClasses;

    virtual void NextChaseTarget_Implementation() override;

private:
    UPROPERTY()
    TObjectPtr<class UStaticMeshComponent> ChaseTargetMesh;

    UPROPERTY(ReplicatedUsing = OnRep_CurrentChaseTargetClassIndex)
    int32 CurrentChaseTargetClassIndex = 0;

    UFUNCTION()
    void OnRep_CurrentChaseTargetClassIndex();

    UFUNCTION(Server, Reliable)
    void Server_SetCurrentChaseTargetClassIndex(int32 NewIndex);

    UFUNCTION()
    void HandleChaseTargetMeshVisibility(const bool NewVisibility);

    void UpdateChaseTargetMesh();
};
