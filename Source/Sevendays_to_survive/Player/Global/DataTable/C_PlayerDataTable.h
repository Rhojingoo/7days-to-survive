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
struct FC_PlayerCommonValue : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float JumpZVelocity=0.0f; // 캐릭터 점프력

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float WalkSpeed=0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float RunSpeed=0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int stamina=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int staminaCalValue=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int staminaAttValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int staminaJumpValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int Hp=0.0f;

};


USTRUCT(BlueprintType)
struct FC_CameraValue : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float TargetArmLength=0.0f; // 암 길이 (카메라 봉)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float CameraRotSpeed=0.0f; // 카메라 회전 속도

};

USTRUCT(BlueprintType)
struct FC_BulletValue : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TSubclassOf<AActor> BulletClass1;
};

USTRUCT(BlueprintType)
struct FC_PlayerDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FC_PlayerCommonValue PlayerValue;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FC_CameraValue CameraValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FC_BulletValue BulletValue;

};
