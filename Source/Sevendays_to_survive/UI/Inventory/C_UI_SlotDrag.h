// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


#include"C_UI_SlotDrag.generated.h"


/**
 * 
 */

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
	UFUNCTION(BlueprintImplementableEvent)
	void CopySlotItemImage(UTexture2D* _Image);
	

	FString GetItemName();


private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Itemname;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTexture2D* ItemImage;
	UWidget* CurWidget;

};
