
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

#include"C_UI_SlotDrag.generated.h"


/**
 * 
 */
class UC_UI_InventorySlot;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_UI_SlotDrag : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void InitSlotinfo();
	UFUNCTION(BlueprintImplementableEvent)
	void DragImage();

	UFUNCTION(BlueprintImplementableEvent)
	UWidget* DragCurWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void CopySlotName(const FString& _Name);
	/*UFUNCTION(BlueprintImplementableEvent)*/
	UFUNCTION(BlueprintImplementableEvent)
	void CopySlotItemImage(UTexture2D* _Image);

	UFUNCTION(BlueprintCallable)
	void SetCurSlot(UC_UI_InventorySlot* _Slots);
	UFUNCTION(BlueprintCallable)
	UC_UI_InventorySlot* GetCurSlot();
	UFUNCTION()
	FString GetItemName();
	UFUNCTION()
	UTexture2D* GetDragItemImage();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UC_UI_InventorySlot* CurSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Itemname;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTexture2D* ItemImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidget* CurWidget;
	

};
