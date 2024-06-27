// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "Delegates/Delegate.h"
#include "Map/C_Items.h"
#include "C_InventoryComponent.generated.h"

// NOTICE: 임시로 비효율적으로 구현
UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
	int Num() const;

	UFUNCTION(BlueprintCallable)
	const FC_ItemAndCount& GetItemAndCount(int _X, int _Y) const;

private:
	

private:
	TArray<TArray<FC_ItemAndCount>> Inventory;
};
