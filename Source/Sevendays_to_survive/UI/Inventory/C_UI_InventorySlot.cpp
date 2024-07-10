// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/C_UI_InventorySlot.h"

void UC_UI_InventorySlot::SetIcon(const FC_ItemRow& _ItemData)
{
	ItemIcons.Add(_ItemData.Name,_ItemData.Icon);
	DragSlot->CopySlotName(ItemName);
	DragSlot->CopySlotItemImage(ItemImage);
	//Itemicon = _ItemData.Icon;
	//여기서 될듯 


}


UTexture2D* UC_UI_InventorySlot::GetIcons(FString _Key)
{

	return ItemIcons[_Key]; //아이콘 키 값으로 가져오고 
	

}

void UC_UI_InventorySlot::SetItemNum(int _Num)
{
	Num = _Num;
}

void UC_UI_InventorySlot::GetSlotInfo()
{
	DragSlot->CopySlotName(ItemName);
	DragSlot->CopySlotItemImage(ItemImage);

}

