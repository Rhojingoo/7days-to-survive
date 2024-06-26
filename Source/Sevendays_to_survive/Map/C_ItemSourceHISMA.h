// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Map/C_ItemSourceTableRow.h"

#include "C_ItemSourceHISMA.generated.h"

class UC_Item;
struct FC_ItemAndCount;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_ItemSourceHISMA : public AActor
{
	GENERATED_BODY()
	
public:
	AC_ItemSourceHISMA();


public:
	virtual void Damage(int _Index, int _Damage);

	virtual void GainDropItems();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UHierarchicalInstancedStaticMeshComponent* HISMComponent = nullptr;

	// MaxHP of each instance.
	TMap<int, int> MaxHpMap;

	// HP of each instance.
	TMap<int, int> HpMap;

	// Drop items.
	TArray<FC_ItemAndCount> DropItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Id", meta = (AllowPrivateAccess = "true"))
	FName Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta=(AllowPrivateAccess = "true"))
	FC_ItemSourceTableRow Row;
};
