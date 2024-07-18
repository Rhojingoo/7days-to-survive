// Fill out your copyright notice in the Description page of Project Settings.E
#include "UI/Inventory/C_UI_SlotDrag.h"
#include "Engine/Texture2D.h"
UTexture2D* UC_UI_SlotDrag::GetDragItemImage()
{
	return ItemImage;
}

FString UC_UI_SlotDrag::GetItemName()
{
	return Itemname;
}


void UC_UI_SlotDrag::SetCurSlot(UC_UI_InventorySlot* _Slots)
{
	CurSlot = _Slots;
}

UC_UI_InventorySlot* UC_UI_SlotDrag::GetCurSlot()
{
	return CurSlot;
}