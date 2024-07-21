// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "C_ItemSlot.generated.h"

class UC_Item;
class UC_UI_InverntoryWidget;
class UC_UI_QuickSlot;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API UItemSlot : public UObject
{
    GENERATED_BODY()

public:
    void Init(int _Index, bool _IsInventorySlot = true);

    const UC_Item* GetItem() const;
    int GetCount() const;

    void Empty();
    bool IsEmpty();
    void IncCount(int _Count);
    void DecCount(int _Count);
    void SetSlot(const UC_Item* _Item, int _Count);
    void UpdateUI();

private:
    UC_UI_InverntoryWidget* GetInventoryWidget() const;
    UC_UI_QuickSlot* GetQuickSlotWidget() const;

    int Index = 0;
    const UC_Item* Item = nullptr;
    int Count = 0;
    bool IsInventorySlot = true;
};