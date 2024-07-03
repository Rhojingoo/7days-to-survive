// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "C_STSGlobalFunctions.generated.h"

class UTimelineComponent;
class ALight;
class AC_MapPlayer;
class UC_BuildingComponent;
class UC_InventoryComponent;
class UC_MapInteractionComponent;
class UC_MapDataAsset;

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_STSGlobalFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Content")
	static UC_BuildingComponent* GetBuildingComponent();

	UFUNCTION(BlueprintCallable, Category = "Content")
	static UC_InventoryComponent* GetInventoryComponent();

	UFUNCTION(BlueprintCallable, Category = "Content")
	static UC_MapInteractionComponent* GetMapInteractionComponent();

	UFUNCTION(BlueprintCallable, Category = "Content")
	static AC_MapPlayer* GetMapPlayerCharacter();

	UFUNCTION(BlueprintCallable, Category = "Content")
	static UC_MapDataAsset* GetMapDataAsset();

	UFUNCTION(BlueprintCallable, Category = "Content")
	static void Day_And_Night_Cycle(ALight* _DirectionLight);

private:
	
};
