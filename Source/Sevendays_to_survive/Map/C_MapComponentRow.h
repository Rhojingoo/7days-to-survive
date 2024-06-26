// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Map/C_Items.h"
#include "C_MapComponentRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct SEVENDAYS_TO_SURVIVE_API FC_MapComponentRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UActorComponent> ComponentClass;
};
