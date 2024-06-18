// Fill out your copyright notice in the Description page of Project Settings.


#include "STS/C_STSInstance.h"
#include "BuildingSystem/C_BuildPartTableRow.h"

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
