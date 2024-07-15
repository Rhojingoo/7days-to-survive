// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Texture2D.h"
#include "Map/C_MapEnums.h"
#include "C_Items.generated.h"

USTRUCT(BlueprintType)
struct SEVENDAYS_TO_SURVIVE_API FC_ItemAndCount
{
    GENERATED_BODY()

public:
    UPROPERTY()
    const class UC_Item* Item = nullptr;

    UPROPERTY()
    int Count = 0;
};

UCLASS(BlueprintType)
class SEVENDAYS_TO_SURVIVE_API UC_Item : public UObject
{
    GENERATED_BODY()

public:
    virtual void Init(FName _Id, TArray<FTableRowBase*> _JoinRows);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FName Id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    EItemType Type = EItemType::NONE;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    UTexture2D* Icon = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    TMap<FName, int> CraftMaterials;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    int DropWeight = 0;

public:
    UFUNCTION(BlueprintPure)
    bool IsCraftable() const;

private:
    int RowIndex = 0;
};

UCLASS(BlueprintType)
class SEVENDAYS_TO_SURVIVE_API UC_Material : public UC_Item
{
    GENERATED_BODY()

public:
    void Init(FName _Id, TArray<FTableRowBase*> _JoinRows) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    int MaxCount = 0;

private:
    int RowIndex = 1;
};

UCLASS(BlueprintType)
class SEVENDAYS_TO_SURVIVE_API UC_Weapon : public UC_Item
{
    GENERATED_BODY()
public:
    void Init(FName _Id, TArray<FTableRowBase*> _JoinRows) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    int Damage = 0;

private:
    int RowIndex = 1;
};

UCLASS(BlueprintType)
class SEVENDAYS_TO_SURVIVE_API UC_Consumable : public UC_Item
{
    GENERATED_BODY()
public:
    void Init(FName _Id, TArray<FTableRowBase*> _JoinRows) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    int Hp = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    int Stamina = 0;

private:
    int RowIndex = 1;
};

UCLASS(BlueprintType)
class SEVENDAYS_TO_SURVIVE_API UC_ItemBuildingPart : public UC_Item
{
    GENERATED_BODY()
public:
    void Init(FName _Id, TArray<FTableRowBase*> _JoinRows) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    int MaxHp = 0;

private:
    int RowIndex = 1;
};