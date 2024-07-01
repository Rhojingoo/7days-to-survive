// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Map/C_ItemRows.h"


#include "C_UI_InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_UI_InventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void SetIcon(const FC_ItemRow& _ItemData);
	
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetIcons(FString _Key);


private:
	TMap<FString,UTexture2D*> ItemIcons;
	int Num;
	
	

	
};
