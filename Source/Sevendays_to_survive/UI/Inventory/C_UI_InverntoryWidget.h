// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Player/Global/C_MapPlayer.h"
#include "Components/PanelWidget.h"

#include "UI/Inventory/C_UI_SlotDrag.h"
#include "UI/Inventory/C_UI_InventorySlot.h"
#include"C_UI_InventorySlot.h"

#include "C_UI_InverntoryWidget.generated.h"

class UC_InventoryComponent;
class UC_UI_SlotDrag;

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_UI_InverntoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetIcon(int _Index, UTexture2D* _Icon);

	UFUNCTION(BlueprintImplementableEvent)
	void SetNumber(int _Index, int _Num);


protected:
	
	

	//UFUNCTION(BlueprintCallable)
	//void NativeConstruct() override;


	UFUNCTION(Blueprintcallable)
	void SettingSlots(UPanelWidget* _Pannel);

	UFUNCTION(Blueprintcallable)
	void SwitchSlot(int _PrevIndex, int _ChangeIndex);
	
	UFUNCTION(BlueprintCallable)
	TArray<UWidget*> GetMYSlots();
	UFUNCTION(BlueprintCallable)
	UWidget* FindSlotsIndex(FString _SlotName);
	
	UFUNCTION(BlueprintCallable)
	void CheckSlot(UC_UI_SlotDrag* _DrageSlot, int _nextindex);

	
	

	
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	APlayerController* WidgetPlayerCOntorller;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UC_InventoryComponent* WidgetInventory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AC_MapPlayer* MapPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UWidget*> Slots;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UC_UI_InventorySlot*> CastSlots;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidget* Prevslot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UC_UI_SlotDrag* CurDrageSlot;

	
};
