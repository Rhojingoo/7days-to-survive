// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Map/C_MapEnums.h"
#include "C_MapDataMemory.generated.h"

class UC_STSInstance;
class UC_MapDataAsset;
class UC_Item;

UCLASS(BlueprintType)
class SEVENDAYS_TO_SURVIVE_API UC_MapDataMemory : public UObject
{
    GENERATED_BODY()

    friend UC_STSInstance;

public:
    UFUNCTION(BlueprintPure)
    TArray<FName> GetCraftItems(int _Page, int _PageSize);

    UFUNCTION(BlueprintPure)
    int GetCraftListMaxPage(int _PageSize);

    UFUNCTION(BlueprintPure)
    TArray<FC_ItemAndCount> GetRandomDropItems();

    UFUNCTION(BlueprintPure)
    const UC_Item* FindItem(FName _Id);

private:
    void Init(UC_STSInstance* _Inst);

    int BisectRight(TArray<int>& _Arr, int _Value);

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
    TMap<FName, UC_Item*> Items;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
    TArray<FName> CraftItems;

    // 가중치 기반 아이템 드롭
    TMap<EItemType, TArray<FName>> Type_To_AccDropIds;
    TMap<EItemType, TArray<int>> Type_To_AccDropWeights;

    UC_STSInstance* Inst = nullptr;
    UC_MapDataAsset* Asset = nullptr;
};