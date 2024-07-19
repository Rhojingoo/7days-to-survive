// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_MapDataAsset.h"

#include "Map/C_ItemSourceTableRow.h"

#include "Map/C_Items.h"
#include "STS/C_STSInstance.h"
#include "STS/C_STSMacros.h"

int UC_MapDataAsset::GetItemSourceMaxHp(FName _Id)
{
    return FindItemSourceRow(_Id)->Hp;
}

TMap<FName, int> UC_MapDataAsset::GetItemSourceDropItems(FName _Id)
{
    return FindItemSourceRow(_Id)->DropItems;
}

TSubclassOf<AC_ItemPouch> UC_MapDataAsset::GetItemPouchClass() const
{
    return ItemPouchClass;
}

int UC_MapDataAsset::GetItemBoxMaxHp() const
{
    return ItemBoxMaxHp;
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