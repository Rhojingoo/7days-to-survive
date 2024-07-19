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
	Fire,
	AlmostAtt,
	Reload

};

UENUM(BlueprintType)
enum class EWeaponUseState : uint8
{
	NoWeapon,
	Rifle,
	Rifle2,
	Pistol,
	Pistol2,
	Shotgun,
	Sword,
	Axe,
	bat
};


UENUM(BlueprintType)
enum class EStaticItemSlot : uint8
{
	RSword,
	RAxe,
	RBat,
	SlotMax
};

UENUM(BlueprintType)
enum class ESkerItemSlot : uint8
{
	RRifle,
	RRifle2,
	RPistol,
	RPistol2,
	RShotgun,
	SlotMax
};

UENUM(BlueprintType)
enum class EPlayerMesh : uint8
{
	Player1,
	Player2,
	Player3,
	Player4
};
/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_PlayerEnum : public UObject
{
	GENERATED_BODY()
	
};
