// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/C_UI_InventoryTip.h"
#include "UI/Inventory/C_UI_InventoryTipDetail.h"

void UC_UI_InventoryTip::Refresh(const UC_Item* _Item)
{
    GetDetail()->Refresh(_Item);
}
