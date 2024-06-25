// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_MapDataAsset.h"
#include "BuildingSystem/C_BuildingPartTableRow.h"
#include "Map/C_ItemSourceTableRow.h"

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


TMap<int64, FC_ItemSourceTableRow> UC_MapDataAsset::GetItemSourceDataMap()
{
    TArray<FC_ItemSourceTableRow*> AllRows;
    FString ContextString;
    ItemSourceTable->GetAllRows<FC_ItemSourceTableRow>(ContextString, AllRows);

    TMap<int64, FC_ItemSourceTableRow> DataMap;

    for (FC_ItemSourceTableRow* Row : AllRows)
    {
        int64 Key = reinterpret_cast<int64>(Row->Mesh);
        DataMap.Emplace(Key, *Row);
    }

    return DataMap;
}
