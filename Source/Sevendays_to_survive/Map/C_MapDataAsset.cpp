// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_MapDataAsset.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "BuildingSystem/C_BuildingPartTableRow.h"
#include "Map/C_ItemSourceTableRow.h"
#include "Map/C_ItemRows.h"
#include "Map/C_Items.h"
#include "STS/C_STSInstance.h"
#include "STS/C_STSMacros.h"

void UC_MapDataAsset::Init(UC_STSInstance* _Inst)
{
    Inst = _Inst;

    Type_To_AccDropIds.Emplace(EItemType::Material);
    Type_To_AccDropIds.Emplace(EItemType::Consumable);
    Type_To_AccDropIds.Emplace(EItemType::Weapon);
    Type_To_AccDropWeights.Emplace(EItemType::Material);
    Type_To_AccDropWeights.Emplace(EItemType::Consumable);
    Type_To_AccDropWeights.Emplace(EItemType::Weapon);

    FString ContextString;

    TArray<FName> RowNames = ItemTable->GetRowNames();
    for (FName RowName : RowNames)
    {
        FC_ItemRow* ItemRow = ItemTable->FindRow<FC_ItemRow>(RowName, ContextString);

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
            FC_MaterialRow* TypeRow = MaterialTable->FindRow<FC_MaterialRow>(RowName, ContextString);
            FoundItem = NewObject<UC_Material>();
            FoundItem->Init(RowName, { ItemRow, TypeRow });
            break;
        }
        case EItemType::Weapon:
        {
            FC_WeaponRow* TypeRow = WeaponTable->FindRow<FC_WeaponRow>(RowName, ContextString);
            FoundItem = NewObject<UC_Weapon>();
            FoundItem->Init(RowName, { ItemRow, TypeRow });
            break;
        }
        case EItemType::Consumable:
        {
            FC_ConsumableRow* TypeRow = ConsumableTable->FindRow<FC_ConsumableRow>(RowName, ContextString);
            FoundItem = NewObject<UC_Consumable>();
            FoundItem->Init(RowName, { ItemRow, TypeRow });
            break;
        }
        case EItemType::BuildingPart:
        {
            break;
        }
        default:
            STS_FATAL("[%s] Item type is unset.", __FUNCTION__);
            break;
        }

        Items.Emplace(RowName, FoundItem);

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

TArray<FC_BuildingPartTableRow> UC_MapDataAsset::GetBuildPartData()
{
    if (nullptr == BuildPartTable)
    {
        UE_LOG(LogTemp, Fatal, TEXT("게임 인스턴스의 BuildPartTable이 nullptr입니다."));
    }

    TArray<FC_BuildingPartTableRow*> Data;
    FString ContextString;
    BuildPartTable->GetAllRows(ContextString, Data);

    TArray<FC_BuildingPartTableRow> Ret;
    for (FC_BuildingPartTableRow* Row : Data)
    {
        Ret.Add(*Row);
    }
    return Ret;
}

int UC_MapDataAsset::GetItemSourceMaxHp(FName _Id)
{
    return FindItemSourceRow(_Id)->Hp;
}

TArray<FC_ItemAndCount> UC_MapDataAsset::GetItemSourceDropItems(FName _Id)
{
    TArray<FC_ItemAndCount> DropItems;

    for (TPair<FName, int>& DropItem : FindItemSourceRow(_Id)->DropItems)
    {
        const UC_Item* Item = FindItem(DropItem.Key);
        int Count = DropItem.Value;

        FC_ItemAndCount ItemAndCount;
        ItemAndCount.Item = Item;
        ItemAndCount.Count = Count;
        DropItems.Add(ItemAndCount);
    }

    return DropItems;
}

TSubclassOf<AC_ItemPouch> UC_MapDataAsset::GetItemPouchClass() const
{
    return ItemPouchClass;
}

TArray<FC_ItemAndCount> UC_MapDataAsset::GetRandomDropItems()
{
    TArray<FC_ItemAndCount> Result;

    for (TPair<EItemType, int>& Pair : Type_To_DropPouchCount)
    {
        EItemType Type = Pair.Key;
        int Count = Pair.Value;

        for (int i = 0; i < Count; ++i)
        {
            // None drop test
            int NoneDropTestInt = Inst->GenerateRandomInt(0, 99);

            if (NoneDropTestInt < NoneDropWeights[Type])
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
            
            FC_ItemAndCount ItemAndCount;
            ItemAndCount.Item = FindItem(Id);
            ItemAndCount.Count = Inst->GenerateRandomInt(Type_To_DropItemMinCount[Type], Type_To_DropItemMaxCount[Type]);

            Result.Add(ItemAndCount);
        }
    }

    return Result;
}

const UC_Item* UC_MapDataAsset::FindItem(FName _Id)
{
    if (true == Items.Contains(_Id))
    {
        return Items[_Id];
    }

    return nullptr;
}

FC_ItemSourceTableRow* UC_MapDataAsset::FindItemSourceRow(FName _Id)
{
    FString ContextString;
    FC_ItemSourceTableRow* Row = ItemSourceTable->FindRow<FC_ItemSourceTableRow>(_Id, ContextString);
    if (nullptr == Row)
    {
        UE_LOG(LogTemp, Fatal, TEXT("%s is not a id for ItemSource Table."), *_Id.ToString());
    }
    return Row;
}

int UC_MapDataAsset::BisectRight(TArray<int>& _Arr, int _Value)
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
