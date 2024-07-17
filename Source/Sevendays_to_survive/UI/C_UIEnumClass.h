// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "C_UIEnumClass.generated.h"
/**
 * 
 */



UENUM(BlueprintType)
enum class EUIType : uint8
{
	MainUi,
	Inventory,
	Minimap,
};

UENUM(BlueprintType)
enum class EUIInputMode : uint8
{
	None,
	Game,
	UIOnly
};