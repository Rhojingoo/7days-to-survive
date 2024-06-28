// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/C_InventoryComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "STS/C_STSMacros.h"

UC_InventoryComponent::UC_InventoryComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

void UC_InventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    Inventory.SetNum(R);
    for (int i = 0; i < Inventory.Num(); ++i)
    {
        Inventory[i].SetNum(C);
    }
}

void UC_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UC_InventoryComponent::AddItem(const UC_Item* _Item, int _Count)
{
    if (true == IsFull())
    {
        STS_FATAL("[%s] Inventory is full. Failed to add {Item: %s, Count: %d}.", __FUNCTION__, *_Item->Id.ToString(), _Count);
        return;
    }

    // 이미 가지고 있는 아이템을 추가하는 경우
    if (true == HasItem(_Item))
    {
        FIntPoint Point = ItemIdToPoint[_Item->Id];
        Inventory[Point.X][Point.Y].Count += _Count;
        return;
    }

    // 가지고 있지 않은 아이템을 추가하는 경우
    FIntPoint Point = FindEmptySlot();
    ItemIdToPoint.Emplace(_Item->Id, Point);
    Inventory[Point.X][Point.Y].Item = _Item;
    Inventory[Point.X][Point.Y].Count = _Count;
    ++UsingSlotCount;
}

bool UC_InventoryComponent::HasItem(const UC_Item* _Item) const
{
    return ItemIdToPoint.Contains(_Item->Id);
}

bool UC_InventoryComponent::IsFull() const
{
    return UsingSlotCount == R * C;
}

const FC_ItemAndCount& UC_InventoryComponent::GetItemAndCount(int _X, int _Y) const
{
    return Inventory[_X][_Y];
}

bool UC_InventoryComponent::IsEmptySlot(int _X, int _Y) const
{
    if (false == IsValidPoint({ _X, _Y }))
    {
        STS_FATAL("[%s] (%d, %d) is not a valid point. Can't check whether it's empty.", __FUNCTION__, _X, _Y);
        return true;
    }

    return nullptr == Inventory[_X][_Y].Item;
}

FIntPoint UC_InventoryComponent::FindEmptySlot() const
{
    if (true == IsFull())
    {
        STS_FATAL("[%s] Inventory is full. Can't find empty point.", __FUNCTION__);
        return FIntPoint::ZeroValue;
    }

    for (int x = 0; x < R; ++x)
    {
        for (int y = 0; y < C; ++y)
        {
            if (true == IsEmptySlot(x, y))
            {
                return { x, y };
            }
        }
    }

    STS_FATAL("[%s] Inventory is not full, but there is no empty point.", __FUNCTION__);
    return FIntPoint::ZeroValue;
}

bool UC_InventoryComponent::IsValidPoint(FIntPoint _Point) const
{
    if (0 <= _Point.X && _Point.X < R && 0 <= _Point.Y && _Point.Y < C)
    {
        return true;
    }

    return false;
}
