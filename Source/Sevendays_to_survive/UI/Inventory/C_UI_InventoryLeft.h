// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STS/C_STSGlobalFunctions.h"
#include "C_UI_InventoryLeft.generated.h"

class UC_UI_CraftItemButton;

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_UI_InventoryLeft : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void Refresh(int _Page);

	UFUNCTION(BlueprintCallable)
	void IncPage();

	UFUNCTION(BlueprintCallable)
	void DecPage();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int CurPage = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int PageSize = 12;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UC_UI_CraftItemButton*> CraftItemButtons;
};
