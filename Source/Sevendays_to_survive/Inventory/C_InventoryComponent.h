// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "Delegates/Delegate.h"
#include "Map/C_Items.h"
#include "C_InventoryComponent.generated.h"

class UC_UI_InverntoryWidget;
class AC_ItemPouch;
class UC_UI_QuickSlot;

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SEVENDAYS_TO_SURVIVE_API UC_InventoryComponent : public UActorComponent
{
    GENERATED_BODY()


public:
    UC_InventoryComponent();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable)
    void AddItem(const UC_Item* _Item, int _Count);

    UFUNCTION(BlueprintCallable)
    void Swap(int _FromIndex, int _ToIndex);

    UFUNCTION(BlueprintCallable)
    void SwapInvenToQuick(int _FromIndex, int _ToIndex);

    UFUNCTION(BlueprintCallable)
    void SwapQuickToInven(int _FromIndex, int _ToIndex);

    UFUNCTION(BlueprintCallable)
    void SwapQuickToQuick(int _FromIndex, int _ToIndex);


    UFUNCTION(BlueprintCallable)
    void DropItemAll(int _Index);

    UFUNCTION(BlueprintCallable)
    void DropItem(int _Index, int _Count);

    UFUNCTION(BlueprintCallable)
    void IncItemCount(int _Index, int _Count);

    UFUNCTION(BlueprintCallable)
    void DecItemCount(int _Index, int _Count);

    UFUNCTION(BlueprintCallable)
    void IncQuickSlotItemCount(int _Index, int _Count);

    UFUNCTION(BlueprintCallable)
    void DecQuickSlotItemCount(int _Index, int _Count);


    UFUNCTION(BlueprintPure)
    bool HasItemByObject(const UC_Item* _Item) const;

    UFUNCTION(BlueprintPure)
    bool HasItem(FName _Id) const;

    UFUNCTION(BlueprintPure)
    int GetCount(int _Index) const;

    UFUNCTION(BlueprintPure)
    int GetCountByItemId(FName _Id) const;

    UFUNCTION(BlueprintPure)
    bool IsFull() const;

    UFUNCTION(BlueprintPure)
    bool IsEmpty() const;

    UFUNCTION(BlueprintCallable)
    bool IsEmptySlot(int _Index) const;

    UFUNCTION(BlueprintPure)
    bool IsEmptyQuickSlot(int _Index) const;

    UFUNCTION(BlueprintCallable)
    int GetUsingSize() const;

    UFUNCTION(BlueprintCallable)
    int FindEmptySlot() const;

    UFUNCTION(BlueprintCallable)
    int FindNonEmptySlot() const;

    UFUNCTION(BlueprintCallable)
    void Craft(FName _Id);

    UFUNCTION(BlueprintPure)
    bool IsCraftable(FName _Id) const;
private:
    UFUNCTION(Server, Reliable)
    void SpawnItem(FTransform _SpawnTransform, FName _Id, int _Count);
    void SpawnItem_Implementation(FTransform _SpawnTransform, FName _Id, int _Count);

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    int Size = 32;

    //Äü½½·Ô
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    int QuickSize = 8;

private:
    bool IsValidSlot(int _Index) const;
    bool IsValidQuickSlot(int _Index) const;
    FTransform GetItemSpawnTransform() const;
    UC_UI_InverntoryWidget* GetInventoryWidget();
    UC_UI_QuickSlot* GetQuickSlotWidget();
    void RefreshInventoryCore();
    void SetSlot(int _Index, const UC_Item* _Item, int _Count);
    void SetQuickSlot(int _Index, const UC_Item* _Item, int _Count);
private:
    int UsingSize = 0;
    TMap<FName, int> ItemIdToIndex;
    TArray<FC_ItemAndCount> Inventory;
    TArray<FC_ItemAndCount> QuickSlots;

    FC_ItemAndCount NullItem = { nullptr, 0 };
    TSubclassOf<AC_ItemPouch> ItemPouchClass = nullptr;
    float SpawnDistance = 100.0f;
};
