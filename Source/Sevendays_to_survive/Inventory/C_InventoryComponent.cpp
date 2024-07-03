// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/C_InventoryComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "STS/C_STSMacros.h"
#include "STS/C_STSInstance.h"
#include "Map/C_Items.h"
#include "Map/C_ItemPouch.h"
#include "Map/C_MapDataAsset.h"
#include "UI/Inventory/C_UI_InverntoryWidget.h"

UC_InventoryComponent::UC_InventoryComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

void UC_InventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    UC_STSInstance* Inst = GetWorld()->GetGameInstanceChecked<UC_STSInstance>();
    UC_MapDataAsset* MapDataAsset = Inst->GetMapDataAsset();
    ItemPouchClass = MapDataAsset->GetItemPouchClass();

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
        SpawnItem(GetItemSpawnTransform(), _Item, _Count);
        STS_LOG("[DebugOnly] [%s] Inventory is full. Failed to add {Item: %s, Count: %d}.", __FUNCTION__, *_Item->Name, _Count);
        return;
    }

    // 이미 가지고 있는 아이템을 추가하는 경우
    if (true == HasItem(_Item))
    {
        FIntPoint Point = ItemIdToPoint[_Item->Id];
        Inventory[Point.X][Point.Y].Count += _Count;

        int Index = PointToIndex(Point);
        InventoryWidget->SetNumber(Index, Inventory[Point.X][Point.Y].Count);
        return;
    }

    // 가지고 있지 않은 아이템을 추가하는 경우
    FIntPoint Point = FindEmptySlot();
    ItemIdToPoint.Emplace(_Item->Id, Point);
    Inventory[Point.X][Point.Y].Item = _Item;
    Inventory[Point.X][Point.Y].Count = _Count;

    int Index = PointToIndex(Point);
    InventoryWidget->SetIcon(Index, _Item->Icon);
    InventoryWidget->SetNumber(Index, _Count);
    ++UsingSlotCount;
}

void UC_InventoryComponent::DropItemAll(int _Index)
{
    FIntPoint Point = IndexToPoint(_Index);
    FC_ItemAndCount& ItemAndCount = Inventory[Point.X][Point.Y];

    if (nullptr == ItemAndCount.Item)
    {
        STS_FATAL("[%s] Given item is NULL.", __FUNCTION__);
        return;
    }

    if (false == HasItem(ItemAndCount.Item))
    {
        STS_FATAL("[%s] There is no %s in the inventory. Can't drop item.", __FUNCTION__, *ItemAndCount.Item->Name);
        return;
    }

    DropItem(_Index, ItemAndCount.Count);
}

void UC_InventoryComponent::DropItem(int _Index, int _Count)
{
    FIntPoint Point = IndexToPoint(_Index);
    FC_ItemAndCount& ItemAndCount = Inventory[Point.X][Point.Y];

    if (nullptr == ItemAndCount.Item)
    {
        STS_FATAL("[%s] Given item is NULL.", __FUNCTION__);
        return;
    }

    if (false == HasItem(ItemAndCount.Item))
    {
        STS_FATAL("[%s] There is no %s in the inventory. Can't drop item.", __FUNCTION__, *ItemAndCount.Item->Name);
        return;
    }

    if (_Count > ItemAndCount.Count)
    {
        STS_FATAL("[%s] There is only %d of %s in the inventory. But you tried to drop %d of %s.", __FUNCTION__, ItemAndCount.Count, *ItemAndCount.Item->Name, _Count, *ItemAndCount.Item->Name);
        return;
    }
    else if (_Count == ItemAndCount.Count)
    {
        SpawnItem(GetItemSpawnTransform(), ItemAndCount.Item, _Count);

        ItemIdToPoint.Remove(ItemAndCount.Item->Id);
        ItemAndCount = NullItem;

        InventoryWidget->SetIcon(_Index, nullptr);
        InventoryWidget->SetNumber(_Index, 0);
        --UsingSlotCount;
        return;
    }

    SpawnItem(GetItemSpawnTransform(), ItemAndCount.Item, _Count);
    ItemAndCount.Count -= _Count;
    InventoryWidget->SetNumber(_Index, ItemAndCount.Count);
}

bool UC_InventoryComponent::HasItem(const UC_Item* _Item) const
{
    if (nullptr == _Item)
    {
        STS_FATAL("[%s] Given item is NULL.", __FUNCTION__);
        return false;
    }

    return ItemIdToPoint.Contains(_Item->Id);
}

bool UC_InventoryComponent::IsFull() const
{
    return UsingSlotCount == R * C;
}

const FC_ItemAndCount& UC_InventoryComponent::GetItemAndCount(int _X, int _Y) const
{
    if (true == IsEmptySlot(_X, _Y))
    {
        STS_FATAL("[%s] There is no item in (%d, %d).", __FUNCTION__, _X, _Y);
        return NullItem;
    }

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

FIntPoint UC_InventoryComponent::IndexToPoint(int _Index) const
{
    if (_Index < 0 || _Index >= R * C)
    {
        STS_FATAL("[%s] %d is an invalid index.", __FUNCTION__, _Index);
        return { 0, 0 };
    }

    return { _Index / C , _Index % C };
}

int UC_InventoryComponent::PointToIndex(FIntPoint _Point) const
{
    if (false == IsValidPoint(_Point))
    {
        STS_FATAL("[%s] (%d, %d) is an invalid point.", __FUNCTION__, _Point.X, _Point.Y);
        return 0;
    }

    return _Point.X * C + _Point.Y;
}

FTransform UC_InventoryComponent::GetItemSpawnTransform() const
{
    FVector SpawnLocation = GetOwner()->GetActorLocation();
    SpawnLocation += GetOwner()->GetActorForwardVector() * SpawnDistance;

    FTransform SpawnTransform;
    SpawnTransform.SetLocation(SpawnLocation);

    return SpawnTransform;
}

void UC_InventoryComponent::SpawnItem_Implementation(FTransform _SpawnTransform, const UC_Item* _Item, int _Count)
{
    STS_LOG("Spawned %d of %s.", _Count, *_Item->Name);

    TMap<FName, int> Items;
    Items.Emplace(_Item->Id, _Count);

    AC_ItemPouch* ItemPouch = GetWorld()->SpawnActor<AC_ItemPouch>(ItemPouchClass.Get(), _SpawnTransform);
    ItemPouch->SetItems(Items);
}
