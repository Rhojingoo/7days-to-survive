// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "STSBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_EDITOR_API USTSBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	static TArray<FString> ItemNameList;
	static TMap<FString, TArray<FString>> AllNameList;
	static FString FolderName;

	UFUNCTION(BlueprintCallable, Category = "Data")
	static void ItemDataTableSetting(UDataTable* DataTable, FString& _FolderName);

	UFUNCTION(BlueprintCallable, Category = "Data")
	static void BuildingPartDataTableSetting(UDataTable* DataTable);

	UFUNCTION(BlueprintCallable, Category = "Data")
	static void ItemTypeCheck(FString _FolderName, EItemType& ItemType);

	UFUNCTION(BlueprintCallable, Category = "Data")
	static void ConsumableDataRowSetting(UDataTable* DataTable, EItemType ItemType);

	UFUNCTION(BlueprintCallable, Category = "Data")
	static void MaterialDataRowSetting(UDataTable* DataTable, EItemType ItemTyp);

	UFUNCTION(BlueprintCallable, Category = "Data")
	static void WeaponDataRowSetting(UDataTable* DataTable, EItemType ItemTyp);




		
};
