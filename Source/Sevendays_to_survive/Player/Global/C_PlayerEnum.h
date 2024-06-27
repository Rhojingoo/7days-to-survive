// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "C_PlayerEnum.generated.h"


UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Move,
	Look,
	Run,
	Jump,
	Aim,
	Punch,
	Crouch

};

UENUM(BlueprintType)
enum class EWeaponUseState : uint8
{
	NoWeapon,
	Rifle,
	Pistol,
	Shotgun,
	Sword,
	Axe
};


UENUM(BlueprintType)
enum class EPlayerItemSlot : uint8
{
	None,
	LWeapon,
	RWeapon,
	SlotMax
};
/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_PlayerEnum : public UObject
{
	GENERATED_BODY()
	
};
