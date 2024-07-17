// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/C_UI_QuickSlot.h"

void UC_UI_QuickSlot::TileViewInitialze(UTileView* _Tileview, int _InitCount)
{
	//타일 설정
	for (size_t i = 0; i < _InitCount; i++)
	{
		UC_UI_InventorySlot* Object = NewObject<UC_UI_InventorySlot>(this);
		QuickSlotDataArray.Add(Object);
		_Tileview->AddItem(Object);
	}
}
/*
FString UC_UI_QuickSlot::GetWeaponName(EWeaponUseState* _Type)
{
	FString changeName;
	//changeName = EnumToString(EWeaponUseState::Axe);
	return "None";
}
*/

