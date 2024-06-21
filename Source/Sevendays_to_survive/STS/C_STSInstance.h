// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "C_STSInstance.generated.h"

struct FC_PlayerDataTable;
struct FC_UITableRow;
/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_STSInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	TArray<struct FC_BuildingPartTableRow> GetBuildPartData();

	UFUNCTION(BlueprintCallable)
	TArray<struct FC_UITableRow> GetPlayerInfoData();

	UFUNCTION(BlueprintCallable)
	void SetPlayerInfo(FString _Name, FString _UserIP);

	
	FC_PlayerDataTable* GetPlayerDataTable();
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* BuildPartTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* PlayerDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", meta = (AllowPrivateAccess = "true"));
	UDataTable* DT_UIData;
};
