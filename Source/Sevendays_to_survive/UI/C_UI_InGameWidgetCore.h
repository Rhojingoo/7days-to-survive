// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_UI_InGameWidgetCore.generated.h"

class UC_UI_QuickSlot;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_UI_InGameWidgetCore : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintPure)
	UC_UI_QuickSlot* GetQuickSlotWidget();
};
