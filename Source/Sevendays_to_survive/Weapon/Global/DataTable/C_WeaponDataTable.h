// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "C_WeaponDataTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FC_StaticMeshValue : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	UStaticMesh* StaticMesh;
};


USTRUCT(BlueprintType)
struct FC_SkeletalMeshValue : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	USkeletalMesh* SkeletalMesh;


};

USTRUCT(BlueprintType)
struct FC_WeaponDataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FC_StaticMeshValue WeaponStaticMeshValue;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FC_SkeletalMeshValue WeaponSkeletalMeshValue;
};
