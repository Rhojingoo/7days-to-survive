// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_MapDataAsset.h"
#include "BuildingSystem/C_BuildingPartTableRow.h"
#include "Map/C_ItemSourceTableRow.h"
#include "Map/C_ItemRows.h"
#include "Map/C_Items.h"

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

TArray<TPair<const UC_Item*, int>> UC_MapDataAsset::GetItemSourceDropItems(FName _Id)
{
    TArray<TPair<const UC_Item*, int>> DropItems;
    
    for (TPair<FName, int>& DropItem : FindItemSourceRow(_Id)->DropItems)
    {
        const UC_Item* Item = FindItem(DropItem.Key);
        int Count = DropItem.Value;
        DropItems.Add({Item, Count});
    }

    return DropItems;
}

const UC_Item* UC_MapDataAsset::FindItem(FName _Name)
{
    if (true == Items.Contains(_Name))
    {
        return Items[_Name];
    }

    FString ContextString;
    FC_ItemRow* ItemRow = ItemTable->FindRow<FC_ItemRow>(_Name, ContextString);

    if (nullptr == ItemRow)
    {
        UE_LOG(LogTemp, Fatal, TEXT("%s is undefined item."), *_Name.ToString());
        return nullptr;
    }

    // 데이터 테이블의 행을 UC_Item 오브젝트로 변환해서 저장한다.

    EItemType ItemType = ItemRow->Type;

    UC_Item* FoundItem = nullptr;
    switch (ItemType)
    {
    case EItemType::NONE:
        break;
    case EItemType::Material:
    {
        FC_MaterialRow* TypeRow = MaterialTable->FindRow<FC_MaterialRow>(_Name, ContextString);
        FoundItem = NewObject<UC_Material>();
        FoundItem->Init(ItemRow, TypeRow);
        break;
    }
    case EItemType::Weapon:
    {
        FC_WeaponRow* TypeRow = WeaponTable->FindRow<FC_WeaponRow>(_Name, ContextString);
        FoundItem = NewObject<UC_Weapon>();
        FoundItem->Init(ItemRow, TypeRow);
        break;
    }
        break;
    case EItemType::MAX:
        break;
    default:
        break;
    }

    Items.Emplace(_Name, FoundItem);

    return FoundItem;
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
