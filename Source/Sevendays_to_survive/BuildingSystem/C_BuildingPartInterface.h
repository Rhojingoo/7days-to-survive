// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Components/BoxComponent.h"
#include "C_BuildingPartInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UC_BuildingPartInterface : public UInterface
{
	GENERATED_BODY()
};

class SEVENDAYS_TO_SURVIVE_API IC_BuildingPartInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TArray<UBoxComponent*> GetSockets();
};
