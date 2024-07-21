// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TileView.h"
#include "Components/Image.h"
#include "Player/Global/C_PlayerEnum.h"
#include "Inventory/C_InventoryComponent.h"
#include "C_UI_InverntoryWidget.h"
#include "Components/PanelWidget.h"

#include <UI/Inventory/Remake/C_UI_InventorySlot.h>
#include "C_UI_QuickSlot.generated.h"




class UC_Item;
UCLASS()
/**
 *
 */

class SEVENDAYS_TO_SURVIVE_API UC_UI_QuickSlot : public UC_UI_InverntoryWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(Blueprintcallable)
	void Init(UPanelWidget* _GridPanel);

	UFUNCTION(Blueprintcallable)
	void SettingItemData(FString _Name);

	UFUNCTION()
	void UPdateQuickSlot();

	UFUNCTION(BlueprintCallable)
	void QuickSlotAdd(UWidget* _Widget, FC_ItemRow& _Data);

	UFUNCTION(BlueprintImplementableEvent)
	void SetQuickSlotIcon(int _Index, UTexture2D* _Icon);

	UFUNCTION(BlueprintImplementableEvent)
	void SetQuickSlotNumber(int _Index, int _Count);

	UFUNCTION(BlueprintCallable)
	int GetEmptySlotIndex();

	
	void AddItem(const UC_Item* _Item); // GetEmptySlotIndex 해서 빈 자리 찾고 SetQuickSlotIcon(빈 자리, 아이콘);


	//UFUNCTION(Blueprintcallable)
	//FString GetWeaponName(EWeaponUseState* _Type);
private:
	UPROPERTY(Category = "QuickItem", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UC_UI_InventorySlot*> QuickSlotDataArray;
	UPROPERTY(Category = "QuickItem", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UTexture2D*> ItemDataArray;

	UPROPERTY(Category = "QuickItem", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UInvenItemData*> QuickSlotData;

	UPROPERTY(Category = "QuickItem", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> BPInventorySlotClass;

	UPROPERTY()
	bool InitEnd = false;
};
