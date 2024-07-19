// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TileView.h"
#include "Components/Image.h"
#include "Player/Global/C_PlayerEnum.h"
#include "UI/Inventory/Remake/C_UI_InventorySlot.h"
#include "C_UI_QuickSlot.generated.h"



UCLASS()
/**
 *
 */

class SEVENDAYS_TO_SURVIVE_API UC_UI_QuickSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(Blueprintcallable)
	void TileViewInitialze(UTileView* _Tileview, int _InitCount);

	UFUNCTION(BlueprintImplementableEvent)
	void SetQuickSlotIcon(int _Index, UTexture2D* _Icon);

	UFUNCTION(Blueprintcallable)
	int GetEmptySlotIndex();

	void AddItem(const UC_Item* _Item); // GetEmptySlotIndex �ؼ� �� �ڸ� ã�� SetQuickSlotIcon(�� �ڸ�, ������);


	//UFUNCTION(Blueprintcallable)
	//FString GetWeaponName(EWeaponUseState* _Type);
private:
	UPROPERTY(Category = "QuickItem", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UC_UI_InventorySlot*> QuickSlotDataArray;

	UPROPERTY(Category = "QuickItem", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UInvenItemData*> QuickSlotData;
};
