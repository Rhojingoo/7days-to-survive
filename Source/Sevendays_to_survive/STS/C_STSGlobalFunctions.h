// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "C_STSGlobalFunctions.generated.h"

class UTimelineComponent;
class ALight;
class AC_MapPlayer;
class AC_InGameHUD;
class UC_BuildingComponent;
class UC_InventoryComponent;
class UC_MapInteractionComponent;
class UC_MapDataAsset;
class UC_MapDataMemory;
class UC_UI_InventoryCore;
class UC_STSInstance;

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_STSGlobalFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Content")
	static UC_BuildingComponent* GetBuildingComponent();

	UFUNCTION(BlueprintPure, Category = "Content")
	static UC_InventoryComponent* GetInventoryComponent();

	UFUNCTION(BlueprintPure, Category = "Content")
	static UC_MapInteractionComponent* GetMapInteractionComponent();

	UFUNCTION(BlueprintPure, Category = "Content")
	static AC_MapPlayer* GetMapPlayerCharacter();

	UFUNCTION(BlueprintPure, Category = "Content")
	static UC_STSInstance* GetInst();

	UFUNCTION(BlueprintPure, Category = "Content")
	static UC_MapDataAsset* GetMapDataAsset();

	UFUNCTION(BlueprintPure, Category = "Content")
	static UC_MapDataMemory* GetMapDataMemory();

	UFUNCTION(BlueprintCallable, Category = "Content")
	static void Day_And_Night_Cycle(ALight* _DirectionLight);

	UFUNCTION(BlueprintPure)
	static const UC_Item* FindItem(FName _Id);

	UFUNCTION(BlueprintPure)
	static AC_UI_InGameHUD* GetInGameHUD();

	UFUNCTION(BlueprintPure)
	static UC_UI_InventoryCore* GetInventoryCore();

private:
	
};
