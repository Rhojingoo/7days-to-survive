// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Player/Global/C_PlayerEnum.h"
#include "C_InputActionDatas.generated.h"


/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_InputActionDatas : public UDataAsset
{
	GENERATED_BODY()
public:
	UC_InputActionDatas();
	~UC_InputActionDatas();

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EPlayerState,UInputAction*> Actions;
};
