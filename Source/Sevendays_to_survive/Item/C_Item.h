// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "C_Item.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	NONE,
	Wood,
	Stone,
	Iron,
	MAX,
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct SEVENDAYS_TO_SURVIVE_API FC_Item : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool Countable;
};
