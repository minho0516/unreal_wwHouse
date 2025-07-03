// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UIInteractable : public UInterface
{
    GENERATED_BODY()
};

class ESCAPEFROM408_API IIInteractable
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
    void OnFocused();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
    void OnUnfocused();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
    void Interact();
};
