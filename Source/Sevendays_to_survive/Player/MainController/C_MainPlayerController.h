// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_MainPlayerController.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_MainPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface
};
