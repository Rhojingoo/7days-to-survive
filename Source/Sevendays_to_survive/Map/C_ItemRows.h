// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Map/C_Items.h"
#include "Engine/Texture2D.h"
#include "C_ItemRows.generated.h"

USTRUCT(BlueprintType)
struct SEVENDAYS_TO_SURVIVE_API FC_ItemRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType Type = EItemType::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, int> CraftMaterials;
};

USTRUCT(BlueprintType)
struct SEVENDAYS_TO_SURVIVE_API FC_MaterialRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxCount = 0;
};

USTRUCT(BlueprintType)
struct SEVENDAYS_TO_SURVIVE_API FC_WeaponRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Damage = 0;
};