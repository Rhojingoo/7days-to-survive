// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/C_UI_InventoryLeft.h"
#include "Map/C_MapDataAsset.h"
#include "Map/C_Items.h"
#include "UI/Inventory/C_UI_CraftItemButton.h"
#include "Kismet/KismetMathLibrary.h"

void UC_UI_InventoryLeft::RefreshCraftItemList(int _Page)
{
    UC_MapDataAsset* MapDataAsset = UC_STSGlobalFunctions::GetMapDataAsset();
    TArray<FName> ItemIds = MapDataAsset->GetCraftItems(_Page, PageSize);
    
    for (int i = 0; i < PageSize; ++i)
    {
        if (true == ItemIds.IsValidIndex(i))
        {
            const UC_Item* Item = MapDataAsset->FindItem(ItemIds[i]);

            CraftItemButtons[i]->SetVisibility(ESlateVisibility::Visible);
            CraftItemButtons[i]->SetItemIcon(Item->Icon);
            CraftItemButtons[i]->SetItemName(Item->Name);
        }
        else
        {
            CraftItemButtons[i]->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

void UC_UI_InventoryLeft::IncPage()
{
    UC_MapDataAsset* MapDataAsset = UC_STSGlobalFunctions::GetMapDataAsset();
    CurPage = UKismetMathLibrary::Clamp(CurPage + 1, 0, MapDataAsset->GetCraftListMaxPage(PageSize));
    RefreshCraftItemList(CurPage);
}

void UC_UI_InventoryLeft::DecPage()
{
    UC_MapDataAsset* MapDataAsset = UC_STSGlobalFunctions::GetMapDataAsset();
    CurPage = UKismetMathLibrary::Clamp(CurPage - 1, 0, MapDataAsset->GetCraftListMaxPage(PageSize));
    RefreshCraftItemList(CurPage);
}
