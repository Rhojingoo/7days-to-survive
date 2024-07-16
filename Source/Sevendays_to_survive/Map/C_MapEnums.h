// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "C_MapEnums.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    NONE,
    Material,
    Weapon,
    Consumable,
    BuildingPart,
    MAX,
};

UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_MapEnums : public UObject
{
    GENERATED_BODY()
};