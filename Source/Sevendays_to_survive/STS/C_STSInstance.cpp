// Fill out your copyright notice in the Description page of Project Settings.


#include "STS/C_STSInstance.h"
#include "BuildingSystem/C_BuildPartTableRow.h"
#include "Player/Global/DataTable/C_PlayerDataTable.h"
#include "UI/C_UITableRow.h"


//const FC_PlayerLocationData* UC_STSInstance::GetPlayerArr()
//{
//
//	return PlayerArr;
//}

TArray<FC_BuildPartTableRow> UC_STSInstance::GetBuildPartData()
{
    if (nullptr == BuildPartTable)
    {
        UE_LOG(LogTemp, Fatal, TEXT("���� �ν��Ͻ��� BuildPartTable�� nullptr�Դϴ�."));
    }

    TArray<FC_BuildPartTableRow*> Data;
    BuildPartTable->GetAllRows(TEXT("GetAllRows"), Data);

    TArray<FC_BuildPartTableRow> Ret;
    for (FC_BuildPartTableRow* Row : Data)
    {
        Ret.Add(*Row);
    }
    return Ret;
}

const FC_PlayerDataTable* UC_STSInstance::GetPlayerDataTable()
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
        UE_LOG(LogTemp, Fatal, TEXT("���� �ν��Ͻ��� DT_UIData�� nullptr�Դϴ�."));
    }
   
    TArray<FC_UITableRow*> UIData;
    DT_UIData->GetAllRows(TEXT("GetAllRows"), UIData);
   
    TArray<FC_UITableRow> RealData; //��� ���ذ� �� �ȵ�
    for (FC_UITableRow* DRow : UIData)
    {
        RealData.Add(*DRow);
    }
    return RealData;

}

void UC_STSInstance::SetPlayerInfo(FString _Name, FString _UserIP)
{
    FC_UITableRow Row;
    Row.UserName = _Name;
    Row.UserIp = _UserIP;
    DT_UIData->AddRow(*_Name, Row);
    //ĳ���� �̸�
    //ĳ���� ip�̷��� �Ϸ����߾��!!
}

