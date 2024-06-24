// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UI_ServerTest.h"
#include"STS/C_STSInstance.h"
#include"UI/C_UITableRow.h"

void AUI_ServerTest::BeginPlay()
{
	Super::BeginPlay();

	UC_STSInstance* Inst = GetGameInstance<UC_STSInstance>();

	FString& Port = Inst->TitleToGameInfo.ServerPort;
	int PortNumber = FCString::Atoi(*Port);
	if (PortNumber == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (PortNumber == 0)"), __FUNCTION__, __LINE__);
		PortNumber = 30002;
		// UE_LOG(GIMATLog, Fatal, TEXT("%S(%u)> if (PortNumber == 0)"), __FUNCTION__, __LINE__);
	}

	// FString:: Inst->SideScrollGameInfo.PORT;
	Inst->EnableListenServer(true, PortNumber);

}