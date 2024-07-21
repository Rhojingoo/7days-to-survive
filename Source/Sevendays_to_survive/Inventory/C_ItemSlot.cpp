// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/C_ItemSlot.h"
#include "Map/C_Items.h"
#include "STS/C_STSGlobalFunctions.h"
#include "STS/C_STSMacros.h"
#include "UI/Inventory/C_UI_InventoryCore.h"
#include "UI/Inventory/C_UI_InverntoryWidget.h"
#include "UI/Inventory/C_UI_QuickSlot.h"

void UItemSlot::Init(int _Index, bool _IsInventorySlot)
{
    Index = _Index;
    IsInventorySlot = _IsInventorySlot;
}

const UC_Item* UItemSlot::GetItem() const
{
    return Item;
}

int UItemSlot::GetCount() const
{
    return Count;
}

void UItemSlot::Empty()
{
    Item = nullptr;
    Count = 0;

    UpdateUI();
}

bool UItemSlot::IsEmpty()
{
    return nullptr == Item;
}

void UItemSlot::IncCount(int _Count)
{
    Count += _Count;
    
    UpdateUI();
}

void UItemSlot::DecCount(int _Count)
{
    if (Count == _Count)
    {
        Empty();
        return;
    }

    if (Count < _Count)
    {
#ifdef WITH_EDITOR
        STS_FATAL("[%s] Slot %d has %d of item. Can't decrease %d of item.", __FUNCTION__, Index, Count, _Count);
#endif
        return;
    }

    Count -= _Count;

    UpdateUI();
}

void UItemSlot::SetSlot(const UC_Item* _Item, int _Count)
{
    Item = _Item;
    Count = _Count;

    UpdateUI();
}

void UItemSlot::UpdateUI()
{
    if (true == IsInventorySlot)
    {
        if (nullptr != Item)
        {
            GetInventoryWidget()->SetIcon(Index, Item->Icon);
        }
        else
        {
            GetInventoryWidget()->SetIcon(Index, nullptr);
        }

        GetInventoryWidget()->SetNumber(Index, Count);
    }
    else
    {
        if (nullptr != Item)
        {
            GetQuickSlotWidget()->SetIcon(Index, Item->Icon);
        }
        else
        {
            GetQuickSlotWidget()->SetIcon(Index, nullptr);
        }

        GetQuickSlotWidget()->SetNumber(Index, Count);
    }
}

UC_UI_InverntoryWidget* UItemSlot::GetInventoryWidget() const
{
    UWorld* World = GetWorld();

    if (nullptr == World)
    {
#ifdef WITH_EDITOR
        STS_FATAL("[%s] World is null.", __FUNCTION__);
#endif
    }

    return UC_STSGlobalFunctions::GetInventoryCore(World)->GetInventoryWidget();
}

UC_UI_QuickSlot* UItemSlot::GetQuickSlotWidget() const
{
    UWorld* World = GetWorld();

    if (nullptr == World)
    {
#ifdef WITH_EDITOR
        STS_FATAL("[%s] World is null.", __FUNCTION__);
#endif
    }

    return UC_STSGlobalFunctions::GetQuickSlotWidget(World);
}
