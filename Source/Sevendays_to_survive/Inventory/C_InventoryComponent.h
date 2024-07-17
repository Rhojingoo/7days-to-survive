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

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SEVENDAYS_TO_SURVIVE_API UC_InventoryComponent : public UActorComponent
{
    GENERATED_BODY()


public:
    UC_InventoryComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void AddItem(const UC_Item* _Item, int _Count);

    UFUNCTION(BlueprintCallable)
    void DropItemAll(int _Index);

    UFUNCTION(BlueprintCallable)
    void DropItem(int _Index, int _Count);

    UFUNCTION(BlueprintCallable)
    void IncItemCount(int _Index, int _Count);

    UFUNCTION(BlueprintCallable)
    void DecItemCount(int _Index, int _Count);

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

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    UC_UI_InverntoryWidget* InventoryWidget = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    bool UIActiveness = false;

private:
    bool IsValidSlot(int _Index) const;
    FTransform GetItemSpawnTransform() const;
private:
    int UsingSize = 0;
    TMap<FName, int> ItemIdToIndex;
    TArray<FC_ItemAndCount> Inventory;

    FC_ItemAndCount NullItem = { nullptr, 0 };
    TSubclassOf<AC_ItemPouch> ItemPouchClass = nullptr;
    float SpawnDistance = 100.0f;
};
