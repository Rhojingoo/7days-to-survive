// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Map/C_Items.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "C_UI_MaterialInfoBox.generated.h"

class UC_Item;

/**
 *
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_UI_MaterialInfoBox : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Refresh(const UC_Item* _Item, int _CurCount, int _NeedCount);

	UFUNCTION(BlueprintPure)
	const UC_Item* GetItem();

	UFUNCTION(BlueprintPure, BlueprintImplementableEvent)
	UImage* GetImage();

	UFUNCTION(BlueprintPure, BlueprintImplementableEvent)
	UTextBlock* GetNameText();

	UFUNCTION(BlueprintPure, BlueprintImplementableEvent)
	UTextBlock* GetCountText();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	const UC_Item* Item = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int CurCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int NeedCount = 0;
};
