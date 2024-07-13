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
