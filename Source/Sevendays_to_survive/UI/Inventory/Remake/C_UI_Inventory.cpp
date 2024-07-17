// Fill out your copyright notice in the Description page of Project Settings.



#include "C_UI_Inventory.h"
#include "UI/Inventory/Remake/C_UI_NewSlot.h"


void UC_UI_Inventory::TileViewInitialze(UTileView* _TileView, int _InitCount)
{
	for (size_t i = 0; i < _InitCount; i++)
	{
		UInvenItemData* Object = NewObject<UInvenItemData>(this); //슬롯 생성
		ItemDataArray.Add(Object);
		_TileView->AddItem(Object);
	}
}

void UC_UI_Inventory::PushItemToIndex(UInvenItemData* _Item, int _SlotIndex)
{
	if (0 > _SlotIndex)
	{
		return;
	}

	if (_SlotIndex >= ItemDataArray.Num())
	{
		return;
	}

	ItemDataArray[_SlotIndex]->Copy(_Item);
}
void UC_UI_Inventory::SlotAdd(UWidget* _Widget, UObject* _Data)
{
	UC_UI_NewSlot* SlotWidget = Cast<UC_UI_NewSlot>(_Widget);

	UInvenItemData* ItemData = Cast<UInvenItemData>(_Data);
	ItemData->SlotWidget = SlotWidget;
	SlotWidget->Init(ItemData);
	
	SlotWidget->SetItemCount(ItemData->Count);

}


int UC_UI_Inventory::NullSlotIndex()
{
	for (size_t i = 0; i < ItemDataArray.Num(); i++)
	{
		if (ItemDataArray[i]->Count == 0)
		{
			return i;
		}
			
	}

	return -1; //-1 이면 비어있는 칸 없는거입니다. 



}
