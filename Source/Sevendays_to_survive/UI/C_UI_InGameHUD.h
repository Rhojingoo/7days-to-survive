// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/C_UIEnumClass.h"
#include "UI/C_UITableRow.h"
#include "C_UI_InGameHUD.generated.h"

class UC_UI_InventoryCore;
class UC_UI_QuickSlot;
class UC_UI_InGameMainWidget;
class UC_UI_InGameWidgetCore;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_UI_InGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override; //주요 드로 콜

protected:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;

public:
	UFUNCTION(BlueprintCallable)
	void UIOff(EUIType _Type);

	UFUNCTION(BlueprintCallable)
	void UIOn(EUIType _Type);

	UFUNCTION(BlueprintCallable)
	void UIVisibilitySwitch(EUIType _Type);


	UFUNCTION(BlueprintCallable)
	void UIVisibilitySwitchKey(FKey _Key);

	UFUNCTION(BlueprintCallable)
	void UISetVisibilityKey(FKey _Key, ESlateVisibility _Value);

	UFUNCTION(BlueprintCallable)
	void UISetVisibility(EUIType _Type, ESlateVisibility _Value);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCurZOrder()
	{
		return ++CurZOrder;
	}

	UFUNCTION(BlueprintPure)
	UC_UI_InventoryCore* GetInventoryCore();

	UFUNCTION(BlueprintPure)
	UC_UI_QuickSlot* GetQuickSlotWidget();

protected:
	void BeginPlay() override;

private:
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> MainWidgetClass = nullptr;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UC_UI_InGameMainWidget* MainWidget = nullptr;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UC_UI_InGameWidgetCore* WidgetCore = nullptr;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<EUIType, UUserWidget*> Widgets;


	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<EUIType, FUIWidgetDataRow> WidgetDatas;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))

	TMap<FKey, UUserWidget*> WidgetKeys;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<FKey, FUIWidgetDataRow> WidgetKeyDatas;

	TArray<UUserWidget*> OpenWidget;

	int AllUIViewCount = 0;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int CurZOrder = 0;
};
