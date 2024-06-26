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
	float JumpZVelocity; // ĳ���� ������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float Hp;

};


USTRUCT(BlueprintType)
struct FC_CameraValue : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float TargetArmLength; // �� ���� (ī�޶� ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float CameraRotSpeed; // ī�޶� ȸ�� �ӵ�

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

};
