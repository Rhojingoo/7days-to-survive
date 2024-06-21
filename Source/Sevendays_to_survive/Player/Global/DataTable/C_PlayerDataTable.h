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
struct FC_PlayerValue : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float JumpZVelocity; // 캐릭터 점프력

};

USTRUCT(BlueprintType)
struct FC_CameraValue : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float TargetArmLength; // 암 길이 (카메라 봉)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float CameraRotSpeed; // 카메라 회전 속도

};

USTRUCT(BlueprintType)
struct FC_PlayerDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FC_PlayerValue PlayerValue;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FC_CameraValue CameraValue;

};
