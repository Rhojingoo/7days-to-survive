// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/Remake/C_UI_NewSlot.h"

void UC_UI_NewSlot::Init(UInvenItemData* _Data)
{
	if (_Data == nullptr)
	{
		return;
	}

	Data = _Data;
	//ItemIconImage = Cast<UImage>(GetWidgetFromName(TEXT("Icon"));
	//ItemCountWidget = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount"));
}



void UC_UI_NewSlot::SetItemData(UInvenItemData* _SlotData)
{

	Data->Copy(_SlotData); //슬롯 데이터 카피 
	
}

void UC_UI_NewSlot::SetItemCount(int _Count)
{

	if (0 >= _Count)
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);
		ItemCountWidget->SetVisibility(ESlateVisibility::Hidden);
		return;

	}

	ItemIcon->SetVisibility(ESlateVisibility::Visible);
	ItemCountWidget->SetVisibility(ESlateVisibility::Visible);

	FString CountText = FString::FromInt(_Count);

	ItemCountWidget->SetText(FText::FromString(CountText));
}