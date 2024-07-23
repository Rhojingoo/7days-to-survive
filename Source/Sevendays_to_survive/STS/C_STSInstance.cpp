// Fill out your copyright notice in the Description page of Project Settings.


#include "STS/C_STSInstance.h"
#include "Map/C_MapDataAsset.h"
#include "Map/C_MapDataMemory.h"
#include "Player/Global/DataTable/C_PlayerDataTable.h"
#include "UI/C_UITableRow.h"
#include "Weapon/Global/DataTable/C_WeaponDataTable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "STS/C_STSMacros.h"
#include "Map/C_MonsterSpawnPoint.h"
#include "Monster/C_ZombieBase.h"
#include "Player/Global/DataTable/C_PlayerSpawnData.h"

UC_STSInstance::UC_STSInstance()
{
	RandomStream.GenerateNewSeed();
}

void UC_STSInstance::Init()
{
	Super::Init();

	MapDataMemory = NewObject<UC_MapDataMemory>(this);
	MapDataMemory->Init(this);
}

UC_MapDataAsset* UC_STSInstance::GetMapDataAsset()
{
	return MapDataAsset;
}

UC_MapDataMemory* UC_STSInstance::GetMapDataMemory()
{
	return MapDataMemory;
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

FC_PlayerSpawnData* UC_STSInstance::GetPlayerSpawnDataTable()
{
	if (nullptr == PlayerSpawnDataTable)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == PlayerSpawnDataTable)"), __FUNCTION__, __LINE__);
	}

	FC_PlayerSpawnData* Data = PlayerSpawnDataTable->FindRow<FC_PlayerSpawnData>(TEXT("PlayerBegin"), nullptr);

	if (nullptr == Data)
	{

		/* TArray<USkeletalMesh*> UC_STSInstance::GetPlayerSpawnMesh()
		 {
			 return TArray<USkeletalMesh*>();
		 }*/
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> %s PlayerDataTable Data Is Nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return Data;
}

TArray<USkeletalMesh*> UC_STSInstance::GetPlayerSpawnMesh()
{
	if (nullptr == PlayerSpawnDataTable)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == PlayerSpawnDataTable)"), __FUNCTION__, __LINE__);
	}

	FC_PlayerSpawnData* Data = PlayerSpawnDataTable->FindRow<FC_PlayerSpawnData>(TEXT("PlayerBegin"), nullptr);

	if (nullptr == Data)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> %s PlayerDataTable Data Is Nullptr"), __FUNCTION__, __LINE__);
	}

	return Data->PlayerMeshs;
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

TMap<FName, FUIWidgetDataRow*> UC_STSInstance::GetUIWidgetDataMap()
{
	TMap<FName, FUIWidgetDataRow*> Result;

	if (nullptr == WidgetDataTable)
	{
		STS_FATAL("[%s] WidgetDataTable is null.", __FUNCTION__);
		return Result;
	}

	TArray<FName> RowNames = WidgetDataTable->GetRowNames();
	TArray<FUIWidgetDataRow*> WidgetDatas;
	WidgetDataTable->GetAllRows(TEXT(""), WidgetDatas);

	for (size_t i = 0; i < WidgetDatas.Num(); ++i)
	{
		Result.Emplace(RowNames[i], WidgetDatas[i]);
	}

	return Result;
}

int UC_STSInstance::GenerateRandomInt(int _Min, int _Max)
{
	if (_Min > _Max)
	{
		STS_FATAL("[%s] Can't generate random int. Wrong range was given.", __FUNCTION__);
		return 0;
	}

	return RandomStream.RandRange(_Min, _Max);
}

float UC_STSInstance::GenerateRandomFloat(float _Min, float _Max)
{
	if (_Min > _Max)
	{
		STS_FATAL("[%s] Can't generate random float. Wrong range was given.", __FUNCTION__);
		return 0;
	}

	return RandomStream.FRandRange(_Min, _Max);
}

FVector UC_STSInstance::GenerateRandomVector(FBox2D _Box)
{
	float X = GenerateRandomFloat(_Box.Min.X, _Box.Max.X);
	float Y = GenerateRandomFloat(_Box.Min.Y, _Box.Max.Y);
	return { X, Y, 0.0f };
}

void UC_STSInstance::SetPlayerMesh(EPlayerMesh _Mesh)
{
	PlayerMeshs.Add(_Mesh);
}

void UC_STSInstance::SetSpawnMonster()
{
	for (int i = 0; i < SpawnArray.Num(); ++i) {
		SpawnArray[i]->SetSpawn(true);
	}
}

void UC_STSInstance::AddSpawnPoint(AC_MonsterSpawnPoint* _Point)
{
	if (nullptr != _Point) {
		SpawnArray.Add(_Point);
	}
}

void UC_STSInstance::SetZombieTarget()
{
	int Max = PlayerArray.Num();
	for (int i = 0; i < ZombieArray.Num(); ++i) {
		int RandomInt = GenerateRandomInt(0, Max - 1);
		if (nullptr != ZombieArray[i]) {
			ZombieArray[i]->ForceFindTargetActor(PlayerArray[RandomInt]);
		}
	}
}

void UC_STSInstance::AddZombieArray(AC_ZombieBase* _Zombie)
{
	if (nullptr != _Zombie) {
		ZombieArray.Add(_Zombie);
	}
}

void UC_STSInstance::RemoveZombieArray(AC_ZombieBase* _Zombie)
{
	ZombieArray.Remove(_Zombie);
}

void UC_STSInstance::AddPlayerArray(AActor* _Actor)
{
	PlayerArray.Add(_Actor);
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

FString UC_STSInstance::GetPlayerName()
{
	return PlayerName;
}