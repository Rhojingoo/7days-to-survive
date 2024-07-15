// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Player/Global/C_PlayerEnum.h"
#include "Weapon/C_PickUpWeapon.h"
#include "C_WeaponDataTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FC_WeaponDataTable : public FTableRowBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FName WeaponName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	EWeaponUseState WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float BulletRange = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int MagagineSize = 0; // ¿Á¿Â¿¸

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TSubclassOf<AActor> Equip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	UAnimationAsset* WeaponAnimToPlay = nullptr;
};
