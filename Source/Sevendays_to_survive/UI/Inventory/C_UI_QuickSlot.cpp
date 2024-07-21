// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/C_UI_QuickSlot.h"


void UC_UI_QuickSlot::Init(UPanelWidget* _GridPanel)
{
    if (true == InitEnd)
    {
        return;
    }
    InitEnd = true;

    TArray<UWidget*> ChildWidgets = _GridPanel->GetAllChildren();

    for (int i = 0; i < ChildWidgets.Num(); ++i)
    {
        UC_UI_InventorySlot* QuickSlot = Cast<UC_UI_InventorySlot>(ChildWidgets[i]);

        if (nullptr == QuickSlot)
        {
            continue;
        }

        QuickSlot->SettingSlotType(ESlotType::QuickSlot);
        QuickSlot->SetSlotIndex(i);

        QuickSlotDataArray.Add(QuickSlot);
    }
}

int UC_UI_QuickSlot::GetEmptySlotIndex()
{

    for (size_t i = 0; i < QuickSlotDataArray.Num(); i++)
    {
        // 퀵슬롯에 현재 아무런 데이터가 없는지 InventorySlot에서 확인해주는 함수 필요?
        if (QuickSlotDataArray[i] == nullptr)
        {
            return i;
        }
    }

    return -1;
}

/*
FString UC_UI_QuickSlot::GetWeaponName(EWeaponUseState* _Type)
{
    FString changeName;
    //changeName = EnumToString(EWeaponUseState::Axe);
    return "None";
}
*/

void UC_UI_QuickSlot::SettingItemData(FString _Name)
{
    //_Name :: EnumType::

    int a = 0;
}

void UC_UI_QuickSlot::UPdateQuickSlot()
{
    int a = 0;
}

void UC_UI_QuickSlot::QuickSlotAdd(UWidget* _Widget, FC_ItemRow& _Data)
{
    UC_UI_InventorySlot* SlotWidget = Cast<UC_UI_InventorySlot>(_Widget);

    SlotWidget->GetIcons(_Data.Name);
}
