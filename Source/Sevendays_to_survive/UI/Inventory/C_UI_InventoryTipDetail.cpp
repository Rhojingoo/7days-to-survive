// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/C_UI_InventoryTipDetail.h"
#include "Map/C_Items.h"

void UC_UI_InventoryTipDetail::Refresh(const UC_Item* _Item)
{
    GetItemImage()->SetBrushFromTexture(_Item->Icon);
}
