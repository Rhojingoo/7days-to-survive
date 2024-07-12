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

	float AreaWidth = (TotalArea.Max.Y - TotalArea.Min.Y) / ItemBoxSpawnColumnCount;
	float AreaHeight = (TotalArea.Max.X - TotalArea.Min.X) / ItemBoxSpawnRowCount;

	for (int x = 0; x < ItemBoxSpawnRowCount; ++x)
	{
		for (int y = 0; y < ItemBoxSpawnColumnCount; ++y)
		{
			if (x >= ItemBoxSpawnBorderWidth 
				&& ItemBoxSpawnRowCount - 1 - x >= ItemBoxSpawnBorderWidth 
				&& y >= ItemBoxSpawnBorderWidth 
				&& ItemBoxSpawnColumnCount - 1 - y >= ItemBoxSpawnBorderWidth)
			{
				continue;
			}

			float AreaStartY = TotalArea.Min.Y + y * AreaWidth;
			float AreaStartX = TotalArea.Min.X + x * AreaHeight;

			FBox2D Area = FBox2D{
				{AreaStartX, AreaStartY},
				{AreaStartX + AreaHeight, AreaStartY + AreaWidth}
			};

			for (int c = 0; c < ItemBoxSpawnCountPerArea; ++c)
			{
				FVector RandomVec = Inst->GenerateRandomVector(Area);
				RandomVec.Z = 10000.0f + c * 1000.0f;

				AC_ItemBox* ItemBox = GetWorld()->SpawnActor<AC_ItemBox>(ItemBoxClass.Get());
				ItemBox->SetActorLocation(RandomVec);
			}
		}
	}
}

void AC_7Days_Play_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}

