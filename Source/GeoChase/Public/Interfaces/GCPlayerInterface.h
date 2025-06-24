// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

//
#include "GCPlayerInterface.generated.h"

UINTERFACE(MinimalAPI)
class UGCPlayerInterface : public UInterface
{
    GENERATED_BODY()
};

class GEOCHASE_API IGCPlayerInterface
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GC Player interface")
    void SwitchChaseTarget();

};
