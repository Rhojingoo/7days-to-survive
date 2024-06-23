// Fill out your copyright notice in the Description page of Project Settings.


#include "STS/C_STSInstance.h"
#include "Player/Global/DataTable/C_PlayerDataTable.h"
#include "BuildingSystem/C_BuildingPartTableRow.h"
#include "UI/C_UITableRow.h"

TArray<FC_BuildingPartTableRow> UC_STSInstance::GetBuildPartData()
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

/*

FC_UITableRow* UC_STSInstance::GetUIDataTable()
{
    //첫번째 유저의 아이피를 가져와서 일치하면 접속을 Listen이 가능하게 변경 
    TArray<FC_UITableRow*> arr;
    DT_UIData->GetAllRows<FC_UITableRow>(TEXT("GetAllRows"), arr);
    
    FC_UITableRow* Data = arr[0];
     // 0번째 인덱스랑 일치하면 서버에 접속이 가능하게 하려고 했음 

    return Data;
}

*/


