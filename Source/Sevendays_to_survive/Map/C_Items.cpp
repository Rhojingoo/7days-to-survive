// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_Items.h"

#include "Map/C_ItemRows.h"

void UC_Item::Init(FName _Id, TArray<FTableRowBase*> _JoinRows)
{
    FC_ItemRow* Row = reinterpret_cast<FC_ItemRow*>(_JoinRows[UC_Item::RowIndex]);

    if (nullptr == Row)
    {
        UE_LOG(LogTemp, Fatal, TEXT("Row should be a FC_ItemRow type."));
    }

    Id = _Id;
    Name = Row->Name;
    Type = Row->Type;
    Icon = Row->Icon;
    DropWeight = Row->DropWeight;
}

bool UC_Item::IsCraftable() const
{
    return !CraftMaterials.IsEmpty();
}

void UC_Material::Init(FName _Id, TArray<FTableRowBase*> _JoinRows)
{
    Super::Init(_Id, _JoinRows);

    FC_MaterialRow* Row = reinterpret_cast<FC_MaterialRow*>(_JoinRows[UC_Material::RowIndex]);

    if (nullptr == Row)
    {
        UE_LOG(LogTemp, Fatal, TEXT("Row should be a FC_MaterialRow type."));
    }

    MaxCount = Row->MaxCount;
}

void UC_Weapon::Init(FName _Id, TArray<FTableRowBase*> _JoinRows)
{
    Super::Init(_Id, _JoinRows);

    FC_WeaponRow* TypeRow = reinterpret_cast<FC_WeaponRow*>(_JoinRows[UC_Weapon::RowIndex]);

    if (nullptr == TypeRow)
    {
        UE_LOG(LogTemp, Fatal, TEXT("Row should be a FC_WeaponRow type."));
    }

    Damage = TypeRow->Damage;
}


void UC_Consumable::Init(FName _Id, TArray<FTableRowBase*> _JoinRows)
{
    Super::Init(_Id, _JoinRows);

    FC_ConsumableRow* TypeRow = reinterpret_cast<FC_ConsumableRow*>(_JoinRows[UC_Consumable::RowIndex]);

    if (nullptr == TypeRow)
    {
        UE_LOG(LogTemp, Fatal, TEXT("Row should be a FC_ConsumableRow type."));
    }

    Hp = TypeRow->Hp;

    Stamina = TypeRow->Stamina;
}

void UC_ItemBuildingPart::Init(FName _Id, TArray<FTableRowBase*> _JoinRows)
{
    Super::Init(_Id, _JoinRows);

    FC_ItemBuildingPartRow* TypeRow = reinterpret_cast<FC_ItemBuildingPartRow*>(_JoinRows[UC_ItemBuildingPart::RowIndex]);

    if (nullptr == TypeRow)
    {
        UE_LOG(LogTemp, Fatal, TEXT("Row should be a FC_ItemBuildingPartRow type."));
    }

    MaxHp = TypeRow->MaxHp;
    Mesh = TypeRow->Mesh;
    ActorClass = TypeRow->ActorClass;
    TraceType = TypeRow->TraceType;
}
