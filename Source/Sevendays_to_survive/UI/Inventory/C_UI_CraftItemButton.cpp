// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/C_UI_CraftItemButton.h"
#include "STS/C_STSGlobalFunctions.h"
#include "Inventory/C_InventoryComponent.h"

const UC_Item* UC_UI_CraftItemButton::GetItem()
{
    return Item;
}

void UC_UI_CraftItemButton::Refresh(const UC_Item* _Item)
{
    Item = _Item;

    // 아이콘 수정
    Image->SetBrushFromTexture(Item->Icon);

    // 텍스트 수정
    TextBlock->SetText(FText::FromString(Item->Name));

    // 버튼 활성화/비활성화
    UC_InventoryComponent* InventoryComp = UC_STSGlobalFunctions::GetInventoryComponent(GetWorld());
    if (true == InventoryComp->IsCraftable(Item->Id))
    {
        TextBlock->SetColorAndOpacity(FSlateColor(EStyleColor::AccentBlue));
    }
    else
    {
        TextBlock->SetColorAndOpacity(FSlateColor(EStyleColor::AccentRed));
    }
}