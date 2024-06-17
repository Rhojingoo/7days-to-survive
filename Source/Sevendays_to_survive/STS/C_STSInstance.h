// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "C_STSInstance.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_STSInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	/*UFUNCTION(BlueprintCallable)
	const struct FC_PlayerLocationData* GetPlayerArr();*/

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* PlayerArr;
};
