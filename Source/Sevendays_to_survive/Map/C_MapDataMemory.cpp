// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_MapDataMemory.h"
#include "Map/C_Items.h"
#include "Map/C_ItemRows.h"
#include "Map/C_MapDataAsset.h"
#include "STS/C_STSInstance.h"
#include "STS/C_STSGlobalFunctions.h"
#include "STS/C_STSMacros.h"

void UC_MapDataMemory::Init(UC_STSInstance* _Inst)
{
    Inst = _Inst;
    Asset = _Inst->GetMapDataAsset();

    Type_To_AccDropIds.Emplace(EItemType::Material);
    Type_To_AccDropIds.Emplace(EItemType::Consumable);
    Type_To_AccDropIds.Emplace(EItemType::Weapon);
    Type_To_AccDropWeights.Emplace(EItemType::Material);
    Type_To_AccDropWeights.Emplace(EItemType::Consumable);
    Type_To_AccDropWeights.Emplace(EItemType::Weapon);

    FString ContextString;

    TArray<FName> RowNames = Asset->ItemTable->GetRowNames();
    for (FName RowName : RowNames)
    {
        FC_ItemRow* ItemRow = Asset->ItemTable->FindRow<FC_ItemRow>(RowName, ContextString);

        if (nullptr == ItemRow)
        {
            STS_FATAL("[%s] ItemRow is null.", __FUNCTION__);
            return;
        }

        // Convert FC_ItemRow to UC_Item.
        EItemType ItemType = ItemRow->Type;

        UC_Item* FoundItem = nullptr;
        switch (ItemType)
        {
        case EItemType::Material:
        {
            FC_MaterialRow* TypeRow = Asset->MaterialTable->FindRow<FC_MaterialRow>(RowName, ContextString);
            FoundItem = NewObject<UC_Material>();
            FoundItem->Init(RowName, { ItemRow, TypeRow });
            break;
        }
        case EItemType::Weapon:
        {
            FC_WeaponRow* TypeRow = Asset->WeaponTable->FindRow<FC_WeaponRow>(RowName, ContextString);
            FoundItem = NewObject<UC_Weapon>();
            FoundItem->Init(RowName, { ItemRow, TypeRow });
            break;
        }
        case EItemType::Consumable:
        {
            FC_ConsumableRow* TypeRow = Asset->ConsumableTable->FindRow<FC_ConsumableRow>(RowName, ContextString);
            FoundItem = NewObject<UC_Consumable>();
            FoundItem->Init(RowName, { ItemRow, TypeRow });
            break;
        }
        case EItemType::BuildingPart:
        {
            FC_ItemBuildingPartRow* TypeRow = Asset->BuildingPartTable->FindRow<FC_ItemBuildingPartRow>(RowName, ContextString);
            FoundItem = NewObject<UC_ItemBuildingPart>();
            FoundItem->Init(RowName, { ItemRow, TypeRow });
            break;
        }
        default:
            STS_FATAL("[%s] Item type is unset.", __FUNCTION__);
            break;
        }

        Items.Emplace(RowName, FoundItem);

        if (false == FoundItem->CraftMaterials.IsEmpty())
        {
            CraftItems.Add(FoundItem->Id);
        }

        if (EItemType::BuildingPart == ItemType)
        {
            continue;
        }

        int PrevAcc = 0;
        if (false == Type_To_AccDropWeights[ItemType].IsEmpty())
        {
            PrevAcc = Type_To_AccDropWeights[ItemType].Last();
        }
        Type_To_AccDropWeights[ItemType].Add(PrevAcc + FoundItem->DropWeight);
        Type_To_AccDropIds[ItemType].Add(RowName);
    }
}


TArray<FC_ItemAndCount> UC_MapDataMemory::GetRandomDropItems()
{
    TArray<FC_ItemAndCount> Result;

    for (TPair<EItemType, int>& Pair : Asset->Type_To_DropPouchCount)
    {
        EItemType Type = Pair.Key;
        int Count = Pair.Value;

        for (int i = 0; i < Count; ++i)
        {
            // None drop test
            int NoneDropTestInt = Inst->GenerateRandomInt(0, 99);

            if (NoneDropTestInt < Asset->NoneDropWeights[Type])
            {
                continue;
            }

            // 0 3 1 2 0
            // 0 3 4 6 6 Acc
            /*
            * Rand -> Index
            * 0 -> 1
            * 1 -> 1
            * 2 -> 1
            * 3 -> 2
            * 4 -> 3
            * 5 -> 3
            */

            TArray<int>& AccDropWeights = Type_To_AccDropWeights[Type];
            int TotalAcc = AccDropWeights.Last();
            int RandomInt = Inst->GenerateRandomInt(0, TotalAcc - 1);
            int Index = BisectRight(AccDropWeights, RandomInt);
            FName Id = Type_To_AccDropIds[Type][Index];

            int MinCount = Asset->Type_To_DropItemMinCount[Type];
            int MaxCount = Asset->Type_To_DropItemMaxCount[Type];

            FC_ItemAndCount ItemAndCount;
            ItemAndCount.Item = FindItem(Id);
            ItemAndCount.Count = Inst->GenerateRandomInt(MinCount, MaxCount);

            Result.Add(ItemAndCount);
        }
    }

    return Result;
}


TArray<FName> UC_MapDataMemory::GetCraftItems(int _Page, int _PageSize)
{
    TArray<FName> Result;

    int Page = _Page;
    int MaxPage = GetCraftListMaxPage(_PageSize);

    if (Page < 0)
    {
        Page = 0;
    }

    if (Page > MaxPage)
    {
        Page = MaxPage;
    }

    int Start = Page * _PageSize;
    int End = FMath::Min<int>({ Start + _PageSize - 1, CraftItems.Num() - 1 });

    for (int i = Start; i <= End; ++i)
    {
        Result.Add(CraftItems[i]);
    }

    return Result;
}

int UC_MapDataMemory::GetCraftListMaxPage(int _PageSize)
{
    return (CraftItems.Num() - 1) / _PageSize;
}

int UC_MapDataMemory::BisectRight(TArray<int>& _Arr, int _Value)
{
    // 0 3 1 2 0 Weights
    // 0 3 4 6 6 AccWeights
    /*
    * Rand -> Index
    * 0 -> 1
    * 1 -> 1
    * 2 -> 1
    * 3 -> 2
    * 4 -> 3
    * 5 -> 3
    */

    int L = 0;
    int R = _Arr.Num() - 1;

    while (R - L > 1)
    {
        int M = (L + R) / 2;

        if (_Value < _Arr[M])
        {
            R = M;
        }
        else
        {
            L = M + 1;
        }
    }

    return R;
}

const UC_Item* UC_MapDataMemory::FindItem(FName _Id)
{
    if (true == Items.Contains(_Id))
    {
        return Items[_Id];
    }

    return nullptr;
}