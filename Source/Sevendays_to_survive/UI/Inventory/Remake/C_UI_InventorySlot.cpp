// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/Remake/C_UI_InventorySlot.h"
#include "Components/PanelWidget.h"
#include "Kismet/GameplayStatics.h"
#include "STS/C_STSGlobalFunctions.h"
#include "Inventory/C_InventoryComponent.h"


void UC_UI_InventorySlot::SetIcon(const FC_ItemRow& _ItemData)
{
	ItemIcons.Add(_ItemData.Name, _ItemData.Icon);
	DragSlot->CopySlotName(ItemName);
	DragSlot->CopySlotItemImage(ItemImage);
	//Itemicon = _ItemData.Icon;
	//여기서 될듯 


}


UTexture2D* UC_UI_InventorySlot::GetIcons(FString _Key)
{

	return ItemIcons[_Key]; //아이콘 키 값으로 가져오고 
	//맵에서 아이콘을 가져옴

}



void UC_UI_InventorySlot::SetItemNum(int _Num)
{
	Num = _Num; //아이템 갯수
}



void UC_UI_InventorySlot::GetDragSlotInfo()
{
	DragSlot->CopySlotName(ItemName);
	DragSlot->CopySlotItemImage(ItemImage);

}

UC_UI_InventorySlot* UC_UI_InventorySlot::GetSlotInfo()
{
	return this;

}

FString UC_UI_InventorySlot::GetItemName()
{
	return ItemName;
}



void UC_UI_InventorySlot::GetDragItemData(UC_UI_SlotDrag* _DragSlot)
{
	FString CurDragName = _DragSlot->GetItemName(); //드래그 해서 가지고 있는정보

	UTexture2D* CuuDragImage = _DragSlot->GetDragItemImage();

	if (ItemIcons[CurDragName] == nullptr)
	{
		ItemIcons.Add(CurDragName, CuuDragImage); //아이템이 없으면 넣어주고 
	}




}

void UC_UI_InventorySlot::FindPanelIndex() //슬롯 자신의 인덱스를 가지고 있는다. 
{
	UPanelWidget* ParentPanel = this->GetParent(); //부모 패널을 가져옴
	CurSlotIndex = ParentPanel->GetChildIndex(this); //내 인덱스는 내가 가지고 있다. 
}

void UC_UI_InventorySlot::SetSlotIndex(int _Index)
{
	CurSlotIndex = _Index;

}

int UC_UI_InventorySlot::GetSlotIndex()
{
	return CurSlotIndex;
}

void UC_UI_InventorySlot::ChangeIndex(UC_UI_InventorySlot* _CurSlot)
{
	int SaveIndex = _CurSlot->GetSlotIndex();
	if (CurSlotIndex == SaveIndex)
	{
		return;
	}

	_CurSlot->SetSlotIndex(CurSlotIndex);
	CurSlotIndex = SaveIndex;

}


void UC_UI_InventorySlot::ChangeSlot(UC_UI_InventorySlot* _OtherSlot)
{
	/*if (this->Num == 0)
	{
		this->ChageInfo(_OtherSlot);
		_OtherSlot = nullptr;
	}*/
	
	//_OtherSlot->ChageInfo(static_cast<UC_UI_InventorySlot*>(&SaveSlot));
	ChageInfo(_OtherSlot);
}

void UC_UI_InventorySlot::ChageInfo(UC_UI_InventorySlot* _OtherSlot)
{
	if (this == nullptr)
	{
		return;
	}

	FString Tmp = ItemName;
	this->ItemName = _OtherSlot->ItemName;
	_OtherSlot->ItemName = Tmp;

	UC_InventoryComponent* InvenComp = UC_STSGlobalFunctions::GetInventoryComponent(GetWorld());
	InvenComp->Swap(CurSlotIndex, _OtherSlot->CurSlotIndex);

	
	//this->ItemImage = _OtherSlot->ItemImage;
	//this->Num = _OtherSlot->Num; //수량
	//정보 교환

}

void UC_UI_InventorySlot::SettingSlotType(ESlotType _SlotType)
{
	SlotType = _SlotType;
}