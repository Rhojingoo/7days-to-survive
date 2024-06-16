// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "C_PlayerLocationData.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FC_PlayerLocationData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FC_PlayerLocationData();

	~FC_PlayerLocationData();

public:
	// EditAnywhere �����Ϳ��� ����ϰڴ�. 
	// BlueprintReadWrite �������Ʈ���� ���� ����
	// Category = "Resources"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TArray<TSubclassOf<AActor>> Players;
};