// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/C_UI_InverntoryWidget.h"

#include "Player/Global/C_MapPlayer.h"
#include "Inventory/C_InventoryComponent.h"


//void UC_UI_InverntoryWidget::NativeConstruct()
//{
//	Super::NativeConstruct();
//
//}
//


void UC_UI_InverntoryWidget::SettingSlots(UPanelWidget* _Pannel) // 슬롯 가져오기 
{
	
	Slots = _Pannel->GetAllChildren();
	

		
}


void UC_UI_InverntoryWidget::SwitchSlot(int _PrevIndex, int _ChangeIndex)
{
	int a = 0;
}

void UC_UI_InverntoryWidget::CheckSlot(UC_UI_SlotDrag* _DrageSlot, int _nextindex)
{
	FString nextSlotName = Slots[_nextindex]->GetName();
	_DrageSlot->GetItemName();
	//DropOn 했을대 Slot 의 인덱스를 반환하는것도 괜찮을 듯 한데 
}

TArray<UWidget*> UC_UI_InverntoryWidget::GetMYSlots()
{
	return Slots;
}

UWidget* UC_UI_InverntoryWidget::FindSlotsIndex(FString _SlotName)
{

	for (int i = 0; i < Slots.Num(); i++)
	{
		
		if (Slots[i]->GetName() == _SlotName)
		{
			return Slots[i]; //해당 슬롯이 나온다. 그러면 이 슬롯을채크한다. 
		}
	}

	return 0;
}
