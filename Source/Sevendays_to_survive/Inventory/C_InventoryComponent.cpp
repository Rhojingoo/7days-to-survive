// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/C_InventoryComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "STS/C_STSMacros.h"
#include "STS/C_STSInstance.h"
#include "STS/C_STSGlobalFunctions.h"
#include "Map/C_Items.h"
#include "Map/C_ItemPouch.h"
#include "Map/C_MapDataAsset.h"
#include "UI/Inventory/C_UI_InventoryCore.h"
#include "UI/Inventory/C_UI_QuickSlot.h"
#include "UI/Inventory/C_UI_InverntoryWidget.h"

#include "UI/C_UI_InGameHUD.h"

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
    Inventory.SetNum(Size);
}

void UC_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UC_InventoryComponent::AddItem(const UC_Item* _Item, int _Count)
{
    // 이미 가지고 있는 아이템을 추가하는 경우
    if (true == HasItemByObject(_Item))
    {
        int Index = ItemIdToIndex[_Item->Id];
        Inventory[Index].Count += _Count;
        GetInventoryWidget()->SetNumber(Index, Inventory[Index].Count);
        RefreshInventoryCore();
        return;
    }

    // 인벤토리가 꽉 차 있는 경우
    if (true == IsFull())
    {
        SpawnItem(GetItemSpawnTransform(), _Item->Id, _Count);
        STS_LOG("[DebugOnly] [%s] Inventory is full. Failed to add {Item: %s, Count: %d}.", __FUNCTION__, *_Item->Name, _Count);
        return;
    }

    // 가지고 있지 않은 아이템을 추가하는 경우
    int Index = FindEmptySlot();
    ItemIdToIndex.Emplace(_Item->Id, Index);
    Inventory[Index].Item = _Item;
    Inventory[Index].Count = _Count;

    GetInventoryWidget()->SetIcon(Index, _Item->Icon);
    GetInventoryWidget()->SetNumber(Index, _Count);
    RefreshInventoryCore();

    ++UsingSize;


    ////큇슬롯의 FindEmptySlot 하는 함수도 따로 작성?
    //if (true == IsWeapon(_Item->Type))
    //{
    //    // 큇슬롯에 Empty 슬롯 찾기
    //    int SlotIndex = QuickSlotWidget->GetEmptySlotIndex();
    //    QuickSlotWidget->SetQuickSlotIcon(SlotIndex, _Item->Icon);
    //    
    //}
}

bool UC_InventoryComponent::IsWeapon(EItemType _Type) const
{
    EItemType ItemType = _Type;

    if (EItemType::Weapon == ItemType)
    {
        return true;
    }

    return false;
}




void UC_InventoryComponent::DropItemAll(int _Index)
{
    FC_ItemAndCount& ItemAndCount = Inventory[_Index];

    if (nullptr == ItemAndCount.Item)
    {
        STS_FATAL("[%s] Given item is NULL.", __FUNCTION__);
        return;
    }

    if (false == HasItemByObject(ItemAndCount.Item))
    {
        STS_FATAL("[%s] There is no %s in the inventory. Can't drop item.", __FUNCTION__, *ItemAndCount.Item->Name);
        return;
    }

    DropItem(_Index, ItemAndCount.Count);
}

void UC_InventoryComponent::DropItem(int _Index, int _Count)
{
    FC_ItemAndCount& ItemAndCount = Inventory[_Index];

    if (nullptr == ItemAndCount.Item)
    {
        STS_FATAL("[%s] Given item is NULL.", __FUNCTION__);
        return;
    }

    if (false == HasItemByObject(ItemAndCount.Item))
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
        SpawnItem(GetItemSpawnTransform(), ItemAndCount.Item->Id, _Count);

        ItemIdToIndex.Remove(ItemAndCount.Item->Id);
        ItemAndCount = NullItem;

        GetInventoryWidget()->SetIcon(_Index, nullptr);
        GetInventoryWidget()->SetNumber(_Index, 0);
        RefreshInventoryCore();

        --UsingSize;
        return;
    }

    SpawnItem(GetItemSpawnTransform(), ItemAndCount.Item->Id, _Count);
    ItemAndCount.Count -= _Count;
    GetInventoryWidget()->SetNumber(_Index, ItemAndCount.Count);
    RefreshInventoryCore();
}

void UC_InventoryComponent::IncItemCount(int _Index, int _Count)
{
    if (true == IsEmptySlot(_Index))
    {
        STS_FATAL("[%s] %d is empty slot. Can't increase count.", __FUNCTION__, _Index);
        return;
    }

    Inventory[_Index].Count += _Count;
    RefreshInventoryCore();
}

void UC_InventoryComponent::DecItemCount(int _Index, int _Count)
{
    if (true == IsEmptySlot(_Index))
    {
        STS_FATAL("[%s] %d is empty slot. Can't increase count.", __FUNCTION__, _Index);
        return;
    }

    if (Inventory[_Index].Count < _Count)
    {
        FString ItemName = Inventory[_Index].Item->Name;
        STS_FATAL("[%s] There is %d of %s in the inventory. But you tried to decrease %d of %s.", __FUNCTION__
            , Inventory[_Index].Count, *ItemName, _Count, *ItemName);

        return;
    }
    
    if (Inventory[_Index].Count == _Count)
    {
        ItemIdToIndex.Remove(Inventory[_Index].Item->Id);
        Inventory[_Index].Item = nullptr;
        GetInventoryWidget()->SetIcon(_Index, nullptr);
        --UsingSize;
    }

    Inventory[_Index].Count -= _Count;
    GetInventoryWidget()->SetNumber(_Index, Inventory[_Index].Count);
    RefreshInventoryCore();
}

bool UC_InventoryComponent::HasItemByObject(const UC_Item* _Item) const
{
    if (nullptr == _Item)
    {
        STS_FATAL("[%s] Given item is NULL.", __FUNCTION__);
        return false;
    }

    return ItemIdToIndex.Contains(_Item->Id);
}

bool UC_InventoryComponent::HasItem(FName _Id) const
{
    return ItemIdToIndex.Contains(_Id);
}

int UC_InventoryComponent::GetCount(int _Index) const
{
    if (true == IsEmptySlot(_Index))
    {
        STS_FATAL("[%s] %d is empty slot. Can't get count.", __FUNCTION__, _Index);
        return 0;
    }

    return Inventory[_Index].Count;
}

int UC_InventoryComponent::GetCountByItemId(FName _Id) const
{
    if (false == ItemIdToIndex.Contains(_Id))
    {
        return 0;
    }

    int Index = ItemIdToIndex[_Id];
    return GetCount(Index);
}

bool UC_InventoryComponent::IsFull() const
{
    return UsingSize == Size;
}

bool UC_InventoryComponent::IsEmpty() const
{
    return UsingSize == 0;
}

bool UC_InventoryComponent::IsEmptySlot(int _Index) const
{
    if (false == IsValidSlot(_Index))
    {
        STS_FATAL("[%s] %d is an invalid index. Can't check whether it's empty.", __FUNCTION__, _Index);
        return true;
    }

    return nullptr == Inventory[_Index].Item;
}

int UC_InventoryComponent::GetUsingSize() const
{
    return UsingSize;
}

void UC_InventoryComponent::Craft(FName _Id)
{
    if (false == IsCraftable(_Id))
    {
        STS_FATAL("[%s] %s is not craftable item. Failed to craft.", __FUNCTION__, *_Id.ToString());
        return;
    }

    const UC_Item* CraftItem = UC_STSGlobalFunctions::FindItem(GetWorld(), _Id);

    TMap<FName, int> CraftMaterials = CraftItem->CraftMaterials;

    for (TPair<FName, int>& Pair : CraftMaterials)
    {
        FName MatId = Pair.Key;
        int MatNeedCount = Pair.Value;

        int Index = ItemIdToIndex[MatId];
        DecItemCount(Index, MatNeedCount);
    }

    AddItem(CraftItem, 1);
}

bool UC_InventoryComponent::IsCraftable(FName _Id) const
{
    const UC_Item* CraftItem = UC_STSGlobalFunctions::FindItem(GetWorld(), _Id);

    if (false == IsValid(CraftItem) || false == CraftItem->IsCraftable())
    {
        return false;
    }

    TMap<FName, int> CraftMaterials = CraftItem->CraftMaterials;

    for (TPair<FName, int>& Pair : CraftMaterials)
    {
        FName MatId = Pair.Key;
        int MatNeedCount = Pair.Value;

        if (false == HasItem(MatId))
        {
            return false;
        }

        if (MatNeedCount > GetCountByItemId(MatId))
        {
            return false;
        }
    }

    return true;
}

int UC_InventoryComponent::FindEmptySlot() const
{
    if (true == IsFull())
    {
        STS_FATAL("[%s] Inventory is full. Can't find empty slot.", __FUNCTION__);
        return -1;
    }

    for (int Index = 0; Index < Size; ++Index)
    {
        if (true == IsEmptySlot(Index))
        {
            return Index;
        }
    }

    STS_FATAL("[%s] Inventory is not full, but there is no empty slot. Something is wrong.", __FUNCTION__);
    return -1;
}

int UC_InventoryComponent::FindNonEmptySlot() const
{
    if (true == IsEmpty())
    {
        STS_FATAL("[%s] Inventory is empty. There's no non-empty slot.", __FUNCTION__);
        return -1;
    }

    for (int Index = 0; Index < Size; ++Index)
    {
        if (false == IsEmptySlot(Index))
        {
            return Index;
        }
    }

    STS_FATAL("[%s] Inventory is non-empty. But there's no non-empty slot. Something is wrong.", __FUNCTION__);
    return -1;
}

bool UC_InventoryComponent::IsValidSlot(int _Index) const
{
    if (0 <= _Index && _Index < Size)
    {
        return true;
    }

    return false;
}

FTransform UC_InventoryComponent::GetItemSpawnTransform() const
{
    FVector SpawnLocation = GetOwner()->GetActorLocation();
    SpawnLocation += GetOwner()->GetActorForwardVector() * SpawnDistance;

    FTransform SpawnTransform;
    SpawnTransform.SetLocation(SpawnLocation);

    return SpawnTransform;
}

UC_UI_InverntoryWidget* UC_InventoryComponent::GetInventoryWidget()
{
    return UC_STSGlobalFunctions::GetInventoryCore(GetWorld())->GetInventoryWidget();
}

void UC_InventoryComponent::RefreshInventoryCore()
{
    UC_STSGlobalFunctions::GetInventoryCore(GetWorld())->Refresh();
}

void UC_InventoryComponent::SpawnItem_Implementation(FTransform _SpawnTransform, FName _Id, int _Count)
{
    AC_ItemPouch* ItemPouch = GetWorld()->SpawnActor<AC_ItemPouch>(ItemPouchClass.Get(), _SpawnTransform);
    ItemPouch->SetItemAndCount(_Id, _Count);
}
