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
class UC_UI_QuickSlot;
class UC_STSInstance;

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_STSGlobalFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Content", meta = (WorldContext = "WorldContextObject"))
	static UC_BuildingComponent* GetBuildingComponent(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Content", meta = (WorldContext = "WorldContextObject"))
	static UC_InventoryComponent* GetInventoryComponent(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Content", meta = (WorldContext = "WorldContextObject"))
	static UC_MapInteractionComponent* GetMapInteractionComponent(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Content", meta = (WorldContext = "WorldContextObject"))
	static AC_MapPlayer* GetMapPlayerCharacter(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Content", meta = (WorldContext = "WorldContextObject"))
	static UC_STSInstance* GetInst(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Content", meta = (WorldContext = "WorldContextObject"))
	static UC_MapDataAsset* GetMapDataAsset(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Content", meta = (WorldContext = "WorldContextObject"))
	static UC_MapDataMemory* GetMapDataMemory(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Content")
	static void Day_And_Night_Cycle(ALight* _DirectionLight);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static const UC_Item* FindItem(const UObject* WorldContextObject, FName _Id);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static AC_UI_InGameHUD* GetInGameHUD(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UC_UI_InventoryCore* GetInventoryCore(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UC_UI_QuickSlot* GetQuickSlotWidget(const UObject* WorldContextObject);

private:
	
};
