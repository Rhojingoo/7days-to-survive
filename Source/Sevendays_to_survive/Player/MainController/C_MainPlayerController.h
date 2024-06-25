// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "C_MainPlayerController.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_MainPlayerController : public APlayerController , public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface
	UPROPERTY()
	FGenericTeamId PlayerTeamId;
};
