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
	
public:
	FC_ItemRow() { }
	~FC_ItemRow() { }

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType Type = EItemType::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, int> CraftMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DropWeight = 0;
};

USTRUCT(BlueprintType)
struct SEVENDAYS_TO_SURVIVE_API FC_MaterialRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FC_MaterialRow() { }
	~FC_MaterialRow() { }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxCount = 0;
};

USTRUCT(BlueprintType)
struct SEVENDAYS_TO_SURVIVE_API FC_WeaponRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FC_WeaponRow() {}
	~FC_WeaponRow() {}

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Damage = 0;
};

USTRUCT(BlueprintType)
struct SEVENDAYS_TO_SURVIVE_API FC_ConsumableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FC_ConsumableRow() {}
	~FC_ConsumableRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stamina = 0;
};

USTRUCT(BlueprintType)
struct SEVENDAYS_TO_SURVIVE_API FC_ItemBuildingPartRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FC_ItemBuildingPartRow() {}
	~FC_ItemBuildingPartRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxHp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETraceTypeQuery> TraceType = ETraceTypeQuery::TraceTypeQuery1;
};