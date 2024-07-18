// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/C_UI_InventoryCore.h"
#include "UI/Inventory/C_UI_InventoryLeft.h"
#include "UI/Inventory/C_UI_InventoryTip.h"
#include "UI/Inventory/C_UI_InventoryTipDetail.h"

void UC_UI_InventoryCore::Refresh()
{
    GetInventoryLeft()->RefreshCurPage();
    GetInventoryTip()->GetDetail()->RefreshCurItem();
}
