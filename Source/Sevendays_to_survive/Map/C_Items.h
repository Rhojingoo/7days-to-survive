// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Texture2D.h"
#include "C_Items.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	NONE,
	Material,
	Weapon,
	MAX,
};

USTRUCT(BlueprintType)
struct SEVENDAYS_TO_SURVIVE_API FC_ItemAndCount
{
	GENERATED_BODY()

public:
	const class UC_Item* Item = nullptr;
	int Count = 0;
};

UCLASS(BlueprintType)
class SEVENDAYS_TO_SURVIVE_API UC_Item : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Init(FTableRowBase* _ItemRow, FTableRowBase* _TypeRow) {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemType Type = EItemType::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTexture2D* Icon = nullptr;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ActorClass;*/
protected:
	void InitItem(FTableRowBase* _ItemRow);
};

UCLASS(BlueprintType)
class SEVENDAYS_TO_SURVIVE_API UC_Material : public UC_Item
{
	GENERATED_BODY()

public:
	void Init(FTableRowBase* _ItemRow, FTableRowBase* _TypeRow) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MaxCount = 0;
};

UCLASS(BlueprintType)
class SEVENDAYS_TO_SURVIVE_API UC_Weapon : public UC_Item
{
	GENERATED_BODY()

public:
	void Init(FTableRowBase* _ItemRow, FTableRowBase* _TypeRow) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Damage = 0;
};