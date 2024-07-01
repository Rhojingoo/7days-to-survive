// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "Delegates/Delegate.h"
#include "Map/C_Items.h"
#include "C_InventoryComponent.generated.h"

class UC_UI_InverntoryWidget;

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
    void DropItemAll(const UC_Item* _Item);

    UFUNCTION(BlueprintCallable)
    void DropItem(const UC_Item* _Item, int _Count);

    // UFUNCTION(BlueprintCallable)
    //void UseItem(const UC_Item* _Item);

    UFUNCTION(BlueprintPure)
    bool HasItem(const UC_Item* _Item) const;

    UFUNCTION(BlueprintPure)
    bool IsFull() const;

    UFUNCTION(BlueprintCallable)
    const FC_ItemAndCount& GetItemAndCount(int _X, int _Y) const;

    UFUNCTION(BlueprintCallable)
    bool IsEmptySlot(int _X, int _Y) const;
private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    int R = 10;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    int C = 10;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    UC_UI_InverntoryWidget* InventoryWidget = nullptr;

private:
    FIntPoint FindEmptySlot() const;
    bool IsValidPoint(FIntPoint _Point) const;
    void SpawnItem(const UC_Item* _Item, int _Count);
private:
    int UsingSlotCount = 0;
    TMap<FName, FIntPoint> ItemIdToPoint;
    TArray<TArray<FC_ItemAndCount>> Inventory;

    FC_ItemAndCount NullItem = { nullptr, 0 };
};
