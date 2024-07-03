// Fill out your copyright notice in the Description page of Project Settings.


#include "STS/C_STSInstance.h"
#include "Player/Global/DataTable/C_PlayerDataTable.h"
#include "UI/C_UITableRow.h"
#include "Weapon/Global/DataTable/C_WeaponDataTable.h"

UC_MapDataAsset* UC_STSInstance::GetMapDataAsset()
{
    return MapDataAsset;
}

FMonsterDataRow* UC_STSInstance::GetMonsterData(FName _Name)
{
    if (nullptr == DT_MonsterData)
    {
        UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == PlayerDataTable)"), __FUNCTION__, __LINE__);
    }

    FMonsterDataRow* Data = DT_MonsterData->FindRow<FMonsterDataRow>(_Name, nullptr);

    if (nullptr == Data)
    {
        UE_LOG(LogTemp, Error, TEXT("%S(%u)> %s PlayerDataTable Data Is Nullptr"), __FUNCTION__, __LINE__);
        return nullptr;
    }

    return Data;
}

FC_PlayerDataTable* UC_STSInstance::GetPlayerDataTable()
{
    if (nullptr == PlayerDataTable)
    {
        UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == PlayerDataTable)"), __FUNCTION__, __LINE__);
    }

    FC_PlayerDataTable* Data = PlayerDataTable->FindRow<FC_PlayerDataTable>(TEXT("Player"), nullptr);

    if (nullptr == Data)
    {
        UE_LOG(LogTemp, Error, TEXT("%S(%u)> %s PlayerDataTable Data Is Nullptr"), __FUNCTION__, __LINE__);
        return nullptr;
    }

    return Data;
}

FC_WeaponDataTable* UC_STSInstance::GetWeaPonDataTable(FName _Name)
{
    if (nullptr == WeaponDataTable)
    {
        UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == PlayerDataTable)"), __FUNCTION__, __LINE__);
    }

    FC_WeaponDataTable* Data = WeaponDataTable->FindRow<FC_WeaponDataTable>(_Name, nullptr);

    if (nullptr == Data)
    {
        UE_LOG(LogTemp, Error, TEXT("%S(%u)> %s PlayerDataTable Data Is Nullptr"), __FUNCTION__, __LINE__);
        return nullptr;
    }

    return Data;
}

TArray<FC_UITableRow> UC_STSInstance::GetPlayerInfoData()
{
    if (nullptr == DT_UIData)
    {
        UE_LOG(LogTemp, Fatal, TEXT("게임 인스턴스의 DT_UIData이 nullptr입니다."));
    }
   
    TArray<FC_UITableRow*> UIData;
    DT_UIData->GetAllRows(TEXT("GetAllRows"), UIData);
   
    TArray<FC_UITableRow> RealData; //요거 이해가 잘 안됨
    for (FC_UITableRow* DRow : UIData)
    {
        RealData.Add(*DRow);
    }
    return RealData;

}

//UI
void UC_STSInstance::SetPlayerInfo(FString _Name, FString _UserIP)
{
    FC_UITableRow Row;
    Row.UserName = _Name;
    Row.UserIp = "10101100";
    DT_UIData->AddRow(*_Name, Row);
    int a = 0;
    TArray<FString> UIData;

    TArray<FC_UITableRow*> Rows;
    FString Context;
    DT_UIData->GetAllRows(TEXT("GetAllRows"), Rows);

    Context;


    for (FC_UITableRow* Table : Rows) {
        UE_LOG(LogTemp, Warning, TEXT("%s"), *Table->UserIp);
        UE_LOG(LogTemp, Warning, TEXT("%s"), *Table->UserName);
    }
   
}