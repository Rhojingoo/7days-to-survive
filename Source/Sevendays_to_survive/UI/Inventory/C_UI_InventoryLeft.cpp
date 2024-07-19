// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/C_UI_InventoryLeft.h"
#include "Map/C_MapDataMemory.h"
#include "Map/C_Items.h"
#include "UI/Inventory/C_UI_CraftItemButton.h"
#include "Kismet/KismetMathLibrary.h"

void UC_UI_InventoryLeft::Refresh(int _Page)
{
    UC_MapDataMemory* MapDataMemory = UC_STSGlobalFunctions::GetMapDataMemory(GetWorld());
    TArray<FName> ItemIds = MapDataMemory->GetCraftItems(_Page, PageSize);
    
    for (int i = 0; i < PageSize; ++i)
    {
        if (true == ItemIds.IsValidIndex(i))
        {
            const UC_Item* Item = MapDataMemory->FindItem(ItemIds[i]);

            CraftItemButtons[i]->SetVisibility(ESlateVisibility::Visible);
            CraftItemButtons[i]->Refresh(Item);
        }
        else
        {
            CraftItemButtons[i]->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

void UC_UI_InventoryLeft::RefreshCurPage()
{
    Refresh(CurPage);
}

void UC_UI_InventoryLeft::IncPage()
{
    UC_MapDataMemory* MapDataMemory = UC_STSGlobalFunctions::GetMapDataMemory(GetWorld());
    CurPage = UKismetMathLibrary::Clamp(CurPage + 1, 0, MapDataMemory->GetCraftListMaxPage(PageSize));
    Refresh(CurPage);
}

void UC_UI_InventoryLeft::DecPage()
{
    UC_MapDataMemory* MapDataMemory = UC_STSGlobalFunctions::GetMapDataMemory(GetWorld());
    CurPage = UKismetMathLibrary::Clamp(CurPage - 1, 0, MapDataMemory->GetCraftListMaxPage(PageSize));
    Refresh(CurPage);
}
