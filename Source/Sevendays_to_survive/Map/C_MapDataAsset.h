// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Map/C_MapEnums.h"
#include "C_MapDataAsset.generated.h"

struct FC_BuildingPartTableRow;
struct FC_ItemSourceTableRow;
class UC_STSInstance;
class UC_Item;
class AC_ItemPouch;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_MapDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	void Init();

	UFUNCTION(BlueprintCallable)
	TArray<FC_BuildingPartTableRow> GetBuildPartData();

	UFUNCTION(BlueprintCallable)
	int GetItemSourceMaxHp(FName _Id);

	UFUNCTION(BlueprintCallable)
	const UC_Item* FindItem(FName _Id);

	UFUNCTION(BlueprintCallable)
	TArray<FC_ItemAndCount> GetItemSourceDropItems(FName _Id);

	UFUNCTION(BlueprintCallable)
	TSubclassOf<AC_ItemPouch> GetItemPouchClass() const;

	UFUNCTION(BlueprintCallable)
	TArray<FC_ItemAndCount> GetRandomDropItems();

private:
	FC_ItemSourceTableRow* FindItemSourceRow(FName _Id);

	int BisectRight(TArray<int>& _Arr, int _Value);

private:
	UC_STSInstance* Inst = nullptr;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UDataTable* ConsumableTable = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TMap<FName, UC_Item*> Items;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AC_ItemPouch> ItemPouchClass = nullptr;

	// 가중치 기반 아이템 드롭
	TMap<EItemType, TArray<FName>> Type_To_AccDropIds;
	TMap<EItemType, TArray<int>> Type_To_AccDropWeights;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TMap<EItemType, int> Type_To_DropPouchCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TMap<EItemType, int> Type_To_DropItemMinCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TMap<EItemType, int> Type_To_DropItemMaxCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TMap<EItemType, int> NoneDropWeights;
};
