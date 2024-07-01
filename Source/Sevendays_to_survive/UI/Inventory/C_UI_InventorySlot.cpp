// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/C_UI_InventorySlot.h"

void UC_UI_InventorySlot::SetIcon(const FC_ItemRow& _ItemData)
{
	ItemIcons.Add(_ItemData.Name,_ItemData.Icon);
	//여기서 될듯 


}


UTexture2D* UC_UI_InventorySlot::GetIcons(FString _Key)
{
	
	return ItemIcons[_Key];
	

}

void UC_UI_InventorySlot::SetItemNum(int _Num)
{
	Num = _Num;
}
