// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "C_PlayerSpawnData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FC_PlayerSpawnData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TArray<FVector> PlayerSpawnLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TArray<USkeletalMesh*> PlayerMeshs;
};
