// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Inventory/C_InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Global/C_MapPlayer.h"

#include "C_UI_InverntoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_UI_InverntoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	

	
public:

protected:
	
	

	UFUNCTION(BlueprintCallable)
	void NativeConstruct() override;

private:


	APlayerController* WidgetPlayerCOntorller;

	UC_InventoryComponent* WidgetInventory;

	const FC_ItemAndCount* widget;
	
};
