// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Map/C_ItemRows.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include "UI/Inventory/Remake/C_UI_Inventory.h"
#include "UI/Inventory/C_UI_SlotDrag.h"

#include "C_UI_InventorySlot.generated.h"

/**
 * 
 */
//class UTexture2D;
class UC_UI_SlotDrag;
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_UI_InventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Init(UInvenItemData* _Data);


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

	UFUNCTION(BlueprintCallable)
	void GetDragItemData(UC_UI_SlotDrag* _DragSlot);

	UFUNCTION(BlueprintCallable)
	void FindPanelIndex();

	UFUNCTION(BlueprintCallable)
	void SetSlotIndex(int _Index);

	


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<FString,UTexture2D*> ItemIcons;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UC_UI_SlotDrag* DragSlot = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Num;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int CurSlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite , meta = (AllowPrivateAccess = "true"))
	UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* ItemIconImage;
	UPROPERTY()
	UTextBlock* ItemCountWidget = nullptr;

	UInvenItemData* Data;

	
};
