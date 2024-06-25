// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/C_InventoryComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UC_InventoryComponent::UC_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UC_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Inventory.SetNum(10);
	for (int i = 0; i < Inventory.Num(); ++i)
	{
		Inventory[i].SetNum(10);
	}
}

void UC_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UC_InventoryComponent::AddItem(const UC_Item* _Item, int _Count)
{
	//UKismetSystemLibrary::PrintString();

	for (int i = 0; i < Inventory.Num();++i)
	{
		for (int j = 0; j < Inventory[i].Num(); ++j)
		{
			if (Inventory[i][j].Item == _Item)
			{
				Inventory[i][j].Count += _Count;
				return;
			}
		}
	}

	for (int i = 0; i < Inventory.Num(); ++i)
	{
		for (int j = 0; j < Inventory[i].Num(); ++j)
		{
			if (Inventory[i][j].Item == nullptr)
			{
				Inventory[i][j].Item = _Item;
				Inventory[i][j].Count = _Count;
				return;
			}
		}
	}

	int a = 0;
}
