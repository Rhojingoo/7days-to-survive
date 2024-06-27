// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_Items.h"

#include "Map/C_ItemRows.h"

void UC_Item::InitItem(FTableRowBase* _ItemRow)
{
    FC_ItemRow* ItemRow = reinterpret_cast<FC_ItemRow*>(_ItemRow);

    if (nullptr == ItemRow)
    {
        UE_LOG(LogTemp, Fatal, TEXT("_ItemRow should be a FC_ItemRow type."));
    }

    Name = ItemRow->Name;
    Type = ItemRow->Type;
    Icon = ItemRow->Icon;
}

void UC_Material::Init(FTableRowBase* _ItemRow, FTableRowBase* _TypeRow)
{
    Super::InitItem(_ItemRow);

    FC_MaterialRow* TypeRow = reinterpret_cast<FC_MaterialRow*>(_TypeRow);

    if (nullptr == TypeRow)
    {
        UE_LOG(LogTemp, Fatal, TEXT("_TypeRow should be a FC_MaterialRow type."));
    }

    MaxCount = TypeRow->MaxCount;
}

void UC_Weapon::Init(FTableRowBase* _ItemRow, FTableRowBase* _TypeRow)
{
    Super::InitItem(_ItemRow);

    FC_WeaponRow* TypeRow = reinterpret_cast<FC_WeaponRow*>(_TypeRow);

    if (nullptr == TypeRow)
    {
        UE_LOG(LogTemp, Fatal, TEXT("_TypeRow should be a FC_WeaponRow type."));
    }

    Damage = TypeRow->Damage;
}
