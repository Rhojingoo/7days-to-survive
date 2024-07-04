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
	Zoom,
	Punch,
	Crouch,
	Number1Weapon,
	Number2Weapon,
	NoWeapon,
	PickUp,
	Fire

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
enum class EStaticItemSlot : uint8
{
	RSword,
	RAxe,
	SlotMax
};

UENUM(BlueprintType)
enum class ESkerItemSlot : uint8
{
	LRifle,
	RPistol,
	LShotgun,
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
