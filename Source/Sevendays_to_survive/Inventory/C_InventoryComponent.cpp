// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/C_InventoryComponent.h"

#include "Inventory/C_ItemSlot.h"
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
#include "Player/MainPlayer/C_NickMainPlayer.h"

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

    for (int i = 0; i < Size; ++i)
    {
        UItemSlot* InvenSlot = NewObject<UItemSlot>(this);
        InvenSlot->Init(i, true);

        Inventory.Add(InvenSlot);
    }

    for (int i = 0; i < QuickSize; ++i)
    {
        UItemSlot* QuickSlot = NewObject<UItemSlot>(this);
        QuickSlot->Init(i, false);

        QuickSlots.Add(QuickSlot);
    }
}

int UC_InventoryComponent::GetCurQuickSlot() const
{
    return CurQuickSlot;
}

void UC_InventoryComponent::SetCurQuickSlot(int _Index)
{
    CurQuickSlot = _Index;
}

void UC_InventoryComponent::DecQuickSlotItemCount(int _Index)
{
    QuickSlots[_Index]->DecCount(1);

    if (true == QuickSlots[_Index]->IsEmpty())
    {
        RefreshCurQuickSlot();
    }
}

void UC_InventoryComponent::UseInvenItem(int _Index)
{
    if (true == Inventory[_Index]->IsEmpty() || Inventory[_Index]->GetItem()->Type != EItemType::Consumable)
    {
        return;
    }

    const UC_Item* Item = Inventory[_Index]->GetItem();
    const UC_Consumable* Consumable = Cast<const UC_Consumable>(Item);
    Consumable->Use(GetWorld());
    Inventory[_Index]->DecCount(1);

    if (true == Inventory[_Index]->IsEmpty())
    {
        ItemIdToIndex.Remove(Item->Id);
    }
}

void UC_InventoryComponent::AddItem(const UC_Item* _Item, int _Count)
{
    // 인벤토리에 이미 가지고 있는 아이템을 추가하는 경우
    if (true == HasItemByObject(_Item))
    {
        int Index = ItemIdToIndex[_Item->Id];
        Inventory[Index]->IncCount(_Count);
        RefreshInventoryCore();
        return;
    }

    // TODO: 퀵슬롯에 이미 가지고 있는 아이템을 추가하는 경우
    for (int i = 0; i < QuickSlots.Num(); ++i)
    {
        if (QuickSlots[i]->GetItem() == _Item)
        {
            QuickSlots[i]->IncCount(_Count);
            RefreshInventoryCore();
            return;
        }
    }

    // 인벤토리가 꽉 차 있는 경우
    if (true == IsFull())
    {
        SpawnItem(GetItemSpawnTransform(), _Item->Id, _Count);
        return;
    }

    // 가지고 있지 않은 아이템을 추가하는 경우
    int Index = FindEmptySlot();
    ItemIdToIndex.Emplace(_Item->Id, Index);
    Inventory[Index]->SetSlot(_Item, _Count);
    RefreshInventoryCore();

    ++UsingSize;
}

void UC_InventoryComponent::SwapSlotData(UItemSlot* _FromSlot, UItemSlot* _ToSlot)
{
    const UC_Item* FromItem = _FromSlot->GetItem();
    int FromCount = _FromSlot->GetCount();
    const UC_Item* ToItem = _ToSlot->GetItem();
    int ToCount = _ToSlot->GetCount();

    _FromSlot->SetSlot(ToItem, ToCount);
    _ToSlot->SetSlot(FromItem, FromCount);
}

void UC_InventoryComponent::RefreshCurQuickSlot()
{
    AC_NickMainPlayer* MainPlayer = Cast<AC_NickMainPlayer>(GetOwner());
    MainPlayer->OnQuickSlotSelected(CurQuickSlot);
}


void UC_InventoryComponent::Swap(int _FromIndex, int _ToIndex)
{
    UItemSlot* FromSlot = Inventory[_FromIndex];
    UItemSlot* ToSlot = Inventory[_ToIndex];

    if (false == FromSlot->IsEmpty())
    {
        FName FromItemId = FromSlot->GetItem()->Id;
        ItemIdToIndex[FromItemId] = _ToIndex;
    }

    if (false == ToSlot->IsEmpty())
    {
        FName ToItemId = ToSlot->GetItem()->Id;
        ItemIdToIndex[ToItemId] = _FromIndex;
    }

    SwapSlotData(FromSlot, ToSlot);
}

void UC_InventoryComponent::SwapInvenToQuick(int _FromIndex, int _ToIndex)
{
    UItemSlot* FromSlot = Inventory[_FromIndex];
    UItemSlot* ToSlot = QuickSlots[_ToIndex];

    if (false == FromSlot->IsEmpty())
    {
        // 재료 아이템이나 소비 아이템은 퀵슬롯에 올릴 수 없다.
        if (EItemType::Material == FromSlot->GetItem()->Type
            || EItemType::Consumable == FromSlot->GetItem()->Type)
        {
            return;
        }

        FName FromItemId = FromSlot->GetItem()->Id;
        ItemIdToIndex.Remove(FromItemId);
    }
    
    if (false == ToSlot->IsEmpty())
    {
        FName ToItemId = ToSlot->GetItem()->Id;
        ItemIdToIndex.Emplace(ToItemId, _FromIndex);
    }
    
    SwapSlotData(FromSlot, ToSlot);
    RefreshCurQuickSlot();
}

void UC_InventoryComponent::SwapQuickToInven(int _FromIndex, int _ToIndex)
{
    UItemSlot* FromSlot = QuickSlots[_FromIndex];
    UItemSlot* ToSlot = Inventory[_ToIndex];

    if (false == FromSlot->IsEmpty())
    {
        FName FromItemId = FromSlot->GetItem()->Id;
        ItemIdToIndex.Emplace(FromItemId, _ToIndex);
    }

    if (false == ToSlot->IsEmpty())
    {
        // 재료 아이템이나 소비 아이템은 퀵슬롯에 올릴 수 없다.
        if (EItemType::Material == ToSlot->GetItem()->Type
            || EItemType::Consumable == ToSlot->GetItem()->Type)
        {
            return;
        }

        FName ToItemId = ToSlot->GetItem()->Id;
        ItemIdToIndex.Remove(ToItemId);
    }

    SwapSlotData(FromSlot, ToSlot);
    RefreshCurQuickSlot();
}

void UC_InventoryComponent::SwapQuickToQuick(int _FromIndex, int _ToIndex)
{
    UItemSlot* FromSlot = QuickSlots[_FromIndex];
    UItemSlot* ToSlot = QuickSlots[_ToIndex];

    SwapSlotData(FromSlot, ToSlot);
    RefreshCurQuickSlot();
}

void UC_InventoryComponent::Empty(int _Index)
{
    UItemSlot* Slot = Inventory[_Index];

    if (true == Slot->IsEmpty())
    {
        return;
    }

    const UC_Item* DropItem = Slot->GetItem();
    int DropCount = Slot->GetCount();

    ItemIdToIndex.Remove(DropItem->Id);
    Slot->Empty();
    RefreshInventoryCore();

    --UsingSize;
}

void UC_InventoryComponent::DropItemAll(int _Index)
{
    UItemSlot* Slot = Inventory[_Index];

    if (true == Slot->IsEmpty())
    {
        return;
    }

    const UC_Item* DropItem = Slot->GetItem();
    int DropCount = Slot->GetCount();

    Empty(_Index);
    SpawnItem(GetItemSpawnTransform(), DropItem->Id, DropCount);
}

bool UC_InventoryComponent::HasItemByObject(const UC_Item* _Item) const
{
    if (nullptr == _Item)
    {
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
    if (true == Inventory[_Index]->IsEmpty())
    {
        return 0;
    }

    return Inventory[_Index]->GetCount();
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
        Inventory[Index]->DecCount(MatNeedCount);

        if (true == Inventory[Index]->IsEmpty())
        {
            ItemIdToIndex.Remove(MatId);
        }
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

const UC_Item* UC_InventoryComponent::GetQuickSlotItem(int _Index) const
{
    if (false == IsValidQuickSlot(_Index))
    {
        STS_ERROR("[%s] %d is an invalid quick slot index.", __FUNCTION__, _Index);
        return nullptr;
    }

    return QuickSlots[_Index]->GetItem();
}

const UC_Item* UC_InventoryComponent::GetInvenItem(int _Index) const
{
    if (false == IsValidSlot(_Index))
    {
        STS_ERROR("[%s] %d is an invalid quick slot index.", __FUNCTION__, _Index);
        return nullptr;
    }

    return Inventory[_Index]->GetItem();
}

void UC_InventoryComponent::DebugAddItems()
{
    for (TPair<FName, int> Pair : DebugItems)
    {
        const UC_Item* Item = UC_STSGlobalFunctions::FindItem(GetWorld(), Pair.Key);
        AddItem(Item, Pair.Value);
    }
}

int UC_InventoryComponent::FindEmptySlot() const
{
    if (true == IsFull())
    {
#ifdef WITH_EDITOR
        STS_FATAL("[%s] Inventory is full. Can't find empty slot.", __FUNCTION__);
#endif
        return 0;
    }

    for (int Index = 0; Index < Size; ++Index)
    {
        if (true == Inventory[Index]->IsEmpty())
        {
            return Index;
        }
    }

#ifdef WITH_EDITOR
    STS_FATAL("[%s] Inventory is not full, but there is no empty slot. Something is wrong.", __FUNCTION__);
#endif
    return 0;
}

int UC_InventoryComponent::FindNonEmptySlot() const
{
    if (true == IsEmpty())
    {
#ifdef WITH_EDITOR
        STS_FATAL("[%s] Inventory is empty. There's no non-empty slot.", __FUNCTION__);
#endif
        return 0;
    }

    for (int Index = 0; Index < Size; ++Index)
    {
        if (false == Inventory[Index]->IsEmpty())
        {
            return Index;
        }
    }

#ifdef WITH_EDITOR
    STS_FATAL("[%s] Inventory is non-empty. But there's no non-empty slot. Something is wrong.", __FUNCTION__);
#endif
    return -1;
}

bool UC_InventoryComponent::IsValidSlot(int _Index) const
{
    return 0 <= _Index && _Index < Size;
}

bool UC_InventoryComponent::IsValidQuickSlot(int _Index) const
{
    return 0 <= _Index && _Index < QuickSize;
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

UC_UI_QuickSlot* UC_InventoryComponent::GetQuickSlotWidget()
{
    return UC_STSGlobalFunctions::GetQuickSlotWidget(GetWorld());
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
