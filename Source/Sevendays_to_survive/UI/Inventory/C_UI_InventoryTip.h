// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "C_UI_InventoryTip.generated.h"

class UC_Item;
class UC_UI_InventoryTipDetail;

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_UI_InventoryTip : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void Refresh(const UC_Item* _Item);

	UFUNCTION(BlueprintPure, BlueprintImplementableEvent)
	UC_UI_InventoryTipDetail* GetDetail();
};
