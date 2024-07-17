// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include "UI/Inventory/Remake/C_UI_Inventory.h"
#include "C_UI_NewSlot.generated.h"


/**
 * 
 */
 // Fill out your copyright notice in the Description page of Project Settings.
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_UI_NewSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Init(UInvenItemData* _Data);


	UFUNCTION(BlueprintCallable)
	void SetItemData(class UInvenItemData* _SlotData);

	UFUNCTION(BlueprintCallable)
	void SetItemCount(int _Count);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* ItemIcon;
	UPROPERTY()
	UTextBlock* ItemCountWidget = nullptr;

	UInvenItemData* Data;


};
