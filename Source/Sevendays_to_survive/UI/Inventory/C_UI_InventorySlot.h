// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Map/C_ItemRows.h"
#include "UI/Inventory/C_UI_SlotDrag.h"

#include "C_UI_InventorySlot.generated.h"

/**
 * 
 */

class UC_UI_SlotDrag;
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_UI_InventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void SetIcon(const FC_ItemRow& _ItemData);
	UFUNCTION(BlueprintCallable)
	void GetItemInfo(const UWidget* _PrevSlot);

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetIcons(FString _Key);

	UFUNCTION(BlueprintCallable)
	void SetItemNum(int _Num);

	UFUNCTION(BlueprintCallable)
	void GetSlotInfo();



	


private:
	TMap<FString,UTexture2D*> ItemIcons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite , meta = (AllowPrivateAccess = "true"))
	UTexture2D* ItemImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UC_UI_SlotDrag* DragSlot = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Num;
	
	

	
};
