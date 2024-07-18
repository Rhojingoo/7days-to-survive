// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/C_UI_InventoryTipDetail.h"
#include "Map/C_Items.h"
#include "STS/C_STSGlobalFunctions.h"
#include "Inventory/C_InventoryComponent.h"
#include "UI/Inventory/C_UI_MaterialInfoBox.h"

void UC_UI_InventoryTipDetail::Refresh(const UC_Item* _Item)
{
    GetItemImage()->SetBrushFromTexture(_Item->Icon);

    UC_InventoryComponent* InventoryComp = UC_STSGlobalFunctions::GetInventoryComponent();

    TArray<TPair<FName, int>> CraftMaterials;
    for (TPair<FName, int> Pair : _Item->CraftMaterials)
    {
        CraftMaterials.Add(Pair);
    }

    for (int i = 0; i < CraftMaterials.Num(); ++i)
    {
        FName MatItemId = CraftMaterials[i].Key;
        int NeedCount = CraftMaterials[i].Value;

        const UC_Item* MatItem = UC_STSGlobalFunctions::FindItem(MatItemId);
        MaterialInfoBoxes[i]->SetVisibility(ESlateVisibility::Visible);
        MaterialInfoBoxes[i]->Refresh(MatItem, InventoryComp->GetCountByItemId(MatItemId), NeedCount);
    }

    for (int i = CraftMaterials.Num(); i < MaterialInfoBoxes.Num(); ++i)
    {
        MaterialInfoBoxes[i]->SetVisibility(ESlateVisibility::Hidden);
    }
}
