// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Map/C_ItemSourceTableRow.h"

#include "C_ItemSourceHISMA.generated.h"

class UC_Item;
class UC_ItemAndCount;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_ItemSourceHISMA : public AActor
{
	GENERATED_BODY()
	
public:
	AC_ItemSourceHISMA();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void Damage(int _Index, int _Damage);

	virtual void Damage_Implementation(int _Index, int _Damage) ;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UHierarchicalInstancedStaticMeshComponent* HISMComponent = nullptr;

	// MaxHP of each instance.
	TMap<int, int> MaxHpMap;

	// HP of each instance.
	TMap<int, int> HpMap;

	// Drop items.
	TArray<TPair<const UC_Item*, int>> DropItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Id", meta = (AllowPrivateAccess = "true"))
	FName Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta=(AllowPrivateAccess = "true"))
	FC_ItemSourceTableRow Row;
};
