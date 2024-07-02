// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Map/C_ItemSourceTableRow.h"
#include "Components/WidgetComponent.h"

#include "C_ItemSourceHISMA.generated.h"

class UC_Item;
class AC_MapPlayer;
struct FC_ItemAndCount;
class UC_HealthBar;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_ItemSourceHISMA : public AActor
{
	GENERATED_BODY()
	
public:
	AC_ItemSourceHISMA();


public:
	UFUNCTION(BlueprintCallable)
	virtual void Damage(int _Index, int _Damage, AActor* _HitActor);

	virtual void GainDropItems(AC_MapPlayer* _HitCharacter);

	UFUNCTION(BlueprintCallable)
	void UpdateHpBar(int _Index);

	UFUNCTION(BlueprintCallable)
	void HideHpBar();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UHierarchicalInstancedStaticMeshComponent* HISMComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HpBar = nullptr;

	UC_HealthBar* HpBarWidget = nullptr;

	FTransform HpBarTransform;

	int HpBarTargetIndex = 0;

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

private:
	float TempTimer = 0.0f;
};
