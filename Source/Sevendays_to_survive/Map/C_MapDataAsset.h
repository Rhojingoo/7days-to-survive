// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "C_MapDataAsset.generated.h"

struct FC_BuildingPartTableRow;
struct FC_ItemSourceTableRow;
class UC_Item;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_MapDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TSubclassOf<UActorComponent> GetMapComponentClass(FName _Id);

	UFUNCTION(BlueprintCallable)
	TArray<FC_BuildingPartTableRow> GetBuildPartData();

	UFUNCTION(BlueprintCallable)
	int GetItemSourceMaxHp(FName _Id);

	UFUNCTION(BlueprintCallable)
	const UC_Item* FindItem(FName _Id);

public:
	UFUNCTION(BlueprintCallable)
	TArray<FC_ItemAndCount> GetItemSourceDropItems(FName _Id);

private:
	FC_ItemSourceTableRow* FindItemSourceRow(FName _Id);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* MapComponentTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* BuildPartTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* ItemSourceTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UDataTable* ItemTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UDataTable* MaterialTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UDataTable* WeaponTable = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TMap<FName, UC_Item*> Items;
};
