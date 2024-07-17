// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UI/C_UITableRow.h"
#include "Monster/MonsterData/MonsterDataRow.h"
#include "C_STSInstance.generated.h"

struct FC_PlayerDataTable;
struct FC_WeaponDataTable;
struct FC_UITableRow;
/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_STSInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UC_STSInstance();

	// BeginPlay ����
	void Init() override;

	UFUNCTION(BlueprintCallable)
	class UC_MapDataAsset* GetMapDataAsset();

	FMonsterDataRow* GetMonsterData(FName _Name);

	UFUNCTION(BlueprintCallable)
	TArray<struct FC_UITableRow> GetPlayerInfoData();

	UFUNCTION(BlueprintCallable)
	void SetPlayerInfo(FString _Name, FString _UserIP);

	FC_PlayerDataTable* GetPlayerDataTable();

	FC_WeaponDataTable* GetWeaPonDataTable(FName _Name);

	TMap<FName, FUIWidgetDataRow*> GetUIWidgetDataMap();

	FC_UITableRow TitleToGameInfo;

	int GenerateRandomInt(int _Min, int _Max);
	float GenerateRandomFloat(float _Min, float _Max);
	FVector GenerateRandomVector(FBox2D _Box);

public:
	// �ΰ��� �㳷 ���к���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayorNight", meta = (AllowPrivateAccess = "true"))
	bool IsDay;

	// �ΰ��� ����ī��Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayorNight", meta = (AllowPrivateAccess = "true"))
	int DayCount;

	// �ð�UI�� ���� ���� ����ϴ� �ð� 
	// �ڡڡ�12�������� �ð�����(�㳷 ����)�ڡڡ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayorNight", meta = (AllowPrivateAccess = "true"))
	int Time;

	// ���� �ΰ��ӿ��� UI�ð�
	// �ڡڡ� 06�� ~ 17�� == ��,  18�� ~ 05�� == ��  �ڡڡ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayorNight", meta = (AllowPrivateAccess = "true"))
	int GameUI_Time;

	// �ΰ��ӿ��� ���� �˸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayorNight", meta = (AllowPrivateAccess = "true"))
	bool Game_End;

	// �÷��̾� ���� �˸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayorNight", meta = (AllowPrivateAccess = "true"))
	bool Player_arrive;
	

	UFUNCTION(BlueprintCallable)
	void SetSpawnMonster();
	void AddSpawnPoint(class AC_MonsterSpawnPoint* _Point);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AC_MonsterSpawnPoint*> SpawnArray;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* PlayerDataTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* WeaponDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* DT_UIData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* DT_MonsterData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataAsset", meta = (AllowPrivateAccess = "true"))
	UC_MapDataAsset* MapDataAsset = nullptr;

	FRandomStream RandomStream;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataAsset", meta = (AllowPrivateAccess = "true"))
	UDataTable* WidgetDataTable = nullptr;
};
