// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_UI_InventoryCore.generated.h"

class UC_UI_InverntoryWidget;
class UC_UI_InventoryIcon;
class UC_UI_InventoryLeft;
class UC_UI_InventoryTip;

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_UI_InventoryCore : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, BlueprintImplementableEvent)
	UC_UI_InventoryIcon* GetInventoryIcon();

	UFUNCTION(BlueprintPure, BlueprintImplementableEvent)
	UC_UI_InverntoryWidget* GetInventoryWidget();

	UFUNCTION(BlueprintPure, BlueprintImplementableEvent)
	UC_UI_InventoryLeft* GetInventoryLeft();

	UFUNCTION(BlueprintPure, BlueprintImplementableEvent)
	UC_UI_InventoryTip* GetInventoryTip();

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UC_UI_InverntoryWidget* InventoryWidget = nullptr;*/
};
