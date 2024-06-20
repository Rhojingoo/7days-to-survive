// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "C_PlayerDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FC_PlayerDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float JumpZVelocity=500.f;


	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	bool ShouldMove = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	bool IsFalling = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float GroundSpeed = 0.f;
};
