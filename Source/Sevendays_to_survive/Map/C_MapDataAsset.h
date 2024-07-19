// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Map/C_MapEnums.h"
#include "C_MapDataAsset.generated.h"

class UC_STSInstance;
struct FC_ItemSourceTableRow;
class AC_ItemPouch;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_MapDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

	friend class UC_MapDataMemory;

public:
	UFUNCTION(BlueprintPure)
	int GetItemSourceMaxHp(FName _Id);

	UFUNCTION(BlueprintPure)
	TMap<FName, int> GetItemSourceDropItems(FName _Id);

	UFUNCTION(BlueprintPure)
	TSubclassOf<AC_ItemPouch> GetItemPouchClass() const;

	UFUNCTION(BlueprintCallable)
	int GetItemBoxMaxHp() const;

private:
	FC_ItemSourceTableRow* FindItemSourceRow(FName _Id);

private:
	UC_STSInstance* Inst = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	int ItemBoxMaxHp = 20;

	UPROPERTY(EditDefaultsOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* ItemSourceTable = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UDataTable* ItemTable = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UDataTable* MaterialTable = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UDataTable* WeaponTable = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UDataTable* ConsumableTable = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* BuildingPartTable;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AC_ItemPouch> ItemPouchClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TMap<EItemType, int> Type_To_DropPouchCount;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TMap<EItemType, int> Type_To_DropItemMinCount;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TMap<EItemType, int> Type_To_DropItemMaxCount;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TMap<EItemType, int> NoneDropWeights;
};
