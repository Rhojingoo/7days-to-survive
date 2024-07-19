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

int UC_UI_QuickSlot::GetEmptySlotIndex()
{

	for (size_t i = 0; i < QuickSlotDataArray.Num(); i++)
	{
		// 퀵슬롯에 현재 아무런 데이터가 없는지 InventorySlot에서 확인해주는 함수 필요?
		if (QuickSlotDataArray[i]== nullptr)
		{
			return i;
		}
	}

	return -1;
}

/*
FString UC_UI_QuickSlot::GetWeaponName(EWeaponUseState* _Type)
{
	FString changeName;
	//changeName = EnumToString(EWeaponUseState::Axe);
	return "None";
}
*/

