// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/C_UI_MaterialInfoBox.h"
#include "STS/C_STSGlobalFunctions.h"
#include "Inventory/C_InventoryComponent.h"
#include "Map/C_Items.h"

const UC_Item* UC_UI_MaterialInfoBox::GetItem()
{
    return Item;
}

void UC_UI_MaterialInfoBox::Refresh(const UC_Item* _Item, int _CurCount, int _NeedCount)
{
    Item = _Item;
    CurCount = _CurCount;
    NeedCount = _NeedCount;

    // 아이콘 수정
    GetImage()->SetBrushFromTexture(Item->Icon);

    // 텍스트 수정
    GetNameText()->SetText(FText::FromString(Item->Name));

    FString CountText = FString::FromInt(CurCount);
    CountText += " / ";
    CountText += FString::FromInt(NeedCount);
    GetCountText()->SetText(FText::FromString(CountText));

    // 버튼 활성화/비활성화
    /*UC_InventoryComponent* InventoryComp = UC_STSGlobalFunctions::GetInventoryComponent();
    if (true == InventoryComp->IsCraftable(Item->Id))
    {
        TextBlock->SetColorAndOpacity(FSlateColor(EStyleColor::AccentBlue));
    }
    else
    {
        TextBlock->SetColorAndOpacity(FSlateColor(EStyleColor::AccentRed));
    }*/
}