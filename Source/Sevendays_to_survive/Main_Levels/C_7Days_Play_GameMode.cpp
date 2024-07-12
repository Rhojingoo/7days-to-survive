// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_Levels/C_7Days_Play_GameMode.h"
#include "STS/C_STSInstance.h" // 게임인스턴스
#include "Map/C_ItemBox.h"
#include "Sevendays_to_survive.h"

AC_7Days_Play_GameMode::AC_7Days_Play_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_7Days_Play_GameMode::BeginPlay()
{
	Super::BeginPlay();

	//UC_STSInstance* Inst = GetGameInstance<UC_STSInstance>();
	//if (nullptr == Inst)
	//{
	//	return;
	//}
	//FString& Port = Inst->TitleToGameInfo.ServerPort; //포트 값을 가져와야한다.
	//
	//int PortNumber = FCString::Atoi(*Port);
	//if (PortNumber == 0)
	//{
	//	UE_LOG(SevenDays_Log, Error, TEXT("%S(%u)>if(PortNumber == 0)"), __FUNCTION__, __LINE__);
	//	PortNumber = 30002;
	//}
	//Inst->EnableListenServer(true, PortNumber);
	//IsServer = Inst->TitleToGameInfo.ServerOpenCheck;

	UC_STSInstance* Inst = GetGameInstance<UC_STSInstance>();
	if (nullptr == Inst)
	{
		return;
	}

	for (int i = 0; i < ItemBoxCount; ++i)
	{
		FVector RandomVec = Inst->GenerateRandomVector(FBox2D{ {-89000, -9000}, {-43800, 34000} });
		RandomVec.Z = 10000.0f;

		AC_ItemBox* ItemBox = GetWorld()->SpawnActor<AC_ItemBox>(ItemBoxClass.Get());
		ItemBox->SetActorLocation(RandomVec);
	}
}

void AC_7Days_Play_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

