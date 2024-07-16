// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "C_UI_Inventory.generated.h"

UCLASS(Blueprintable , BlueprintType)
class  UInvenItemData : public UObject
{

	GENERATED_BODY()

public:
	UPROPERTY(Category = "Item", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UUserWidget* SlotWidget;

	UPROPERTY(Category = "Item", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Count = 0;

	void Copy(UInvenItemData* _Data)
	{
		Count = _Data->Count;
	}
};

/**
 *
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_UI_Inventory : public UUserWidget
{
	GENERATED_BODY()

	//UFUNCTION(BlueprintCallable)
	//void TileViewInitialze(UTileView* _TileView, int _InitCount);

	
};
