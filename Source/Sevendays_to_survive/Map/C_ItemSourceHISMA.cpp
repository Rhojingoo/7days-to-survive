// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_ItemSourceHISMA.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "STS/C_STSInstance.h"
#include "Map/C_MapDataAsset.h"
#include "Map/C_ItemSourceTableRow.h"
#include "Map/C_Items.h"
#include "Player/Global/C_MapPlayer.h"
#include "Inventory/C_InventoryComponent.h"
#include "STS/C_STSMacros.h"
#include "UI/C_HealthBar.h"

AC_ItemSourceHISMA::AC_ItemSourceHISMA()
{
	PrimaryActorTick.bCanEverTick = true;

	HISMComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HierarchicalInstancedStaticMesh"));
	SetRootComponent(HISMComponent);

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	HpBar->SetupAttachment(HISMComponent);
	HpBar->SetActive(false);
}

void AC_ItemSourceHISMA::BeginPlay()
{
	Super::BeginPlay();

	if (true == Id.IsNone())
	{
		return;
	}

	UC_STSInstance* Inst = GetWorld()->GetGameInstanceChecked<UC_STSInstance>();
	UC_MapDataAsset* MapDataAsset = Inst->GetMapDataAsset();

	DropItems = MapDataAsset->GetItemSourceDropItems(Id);

	int MaxHp = MapDataAsset->GetItemSourceMaxHp(Id);
	int InstCount = HISMComponent->GetInstanceCount();
	for (int i = 0; i < InstCount; ++i)
	{
		MaxHpMap.Emplace(i, MaxHp);
		HpMap.Emplace(i, MaxHp);
	}

	HpBarWidget = Cast<UC_HealthBar>(HpBar->GetWidget());

	if (nullptr == HpBarWidget)
	{
		STS_FATAL("[%s] HpBarWidget is NULL.", __FUNCTION__);
	}

	HpBarWidget->SetMaxHealth(MaxHp);
}

void AC_ItemSourceHISMA::Damage(int _Index, int _Damage)
{
	if (true == Id.IsNone())
	{
		STS_PRINTSTRING("[%s:%d] Id is not set. Can't be damaged.", *GetName(), _Index);
		return;
	}

	HpMap[_Index] -= _Damage;
	STS_LOG("[%s:%d] damaged by % d", *GetName(), _Index, _Damage);
	STS_LOG("[%s:%d] HP: %d/%d", *GetName(), _Index, HpMap[_Index], MaxHpMap[_Index]);

	if (HpMap[_Index] <= 0)
	{
		bool Result = HISMComponent->RemoveInstance(_Index);

		if (false == Result)
		{
			STS_FATAL("[%s:%d] destroy failed.", *GetName(), _Index);
		}
		else
		{
			STS_PRINTSTRING("[%s:%d] destroyed successfully.", *GetName(), _Index);
		}

		return;
	}

	// 위젯 업데이트
	if (true == HpBar->IsActive() && _Index == HpBarTargetIndex)
	{
		HpBarWidget->SetCurHealth(HpMap[HpBarTargetIndex]);
		HpBarWidget->SetMaxHealth(MaxHpMap[HpBarTargetIndex]);
	}
}

void AC_ItemSourceHISMA::GainDropItems(AC_MapPlayer* _HitCharacter)
{
	UC_InventoryComponent* InventoryComponent = _HitCharacter->GetComponentByClass<UC_InventoryComponent>();
	if (nullptr == InventoryComponent)
	{
		STS_FATAL("[%s] InventoryComponent is NULL.", __FUNCTION__);
	}

	for (FC_ItemAndCount& DropItem : DropItems)
	{
		InventoryComponent->AddItem(DropItem.Item, DropItem.Count);
		STS_LOG("got %d %ss.", DropItem.Count, *DropItem.Item->Name);
	}
}

void AC_ItemSourceHISMA::UpdateHpBar(int _Index)
{
	if (true == Id.IsNone())
	{
		return;
	}

	if (false == HpBar->IsActive())
	{
		HpBar->SetActive(true);
	}

	HpBarTargetIndex = _Index;

	HISMComponent->GetInstanceTransform(_Index, HpBarTransform, true);
	FVector InstLocation = HpBarTransform.GetLocation() + FVector::UpVector * 300.0f;

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	UCameraComponent* Camera = PlayerCharacter->GetComponentByClass<UCameraComponent>();
	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(InstLocation, Camera->GetComponentLocation());
	HpBarTransform.SetRotation(LookAtRot.Quaternion());
	HpBarTransform.SetLocation(InstLocation + LookAtRot.Vector() * 300.0f);

	// HpBar 갱신
	HpBar->SetWorldTransform(HpBarTransform);
	HpBarWidget->SetCurHealth(HpMap[HpBarTargetIndex]);
	HpBarWidget->SetMaxHealth(MaxHpMap[HpBarTargetIndex]);
}

void AC_ItemSourceHISMA::HideHpBar()
{
	if (true == Id.IsNone())
	{
		return;
	}

	if (false == HpBar->IsActive())
	{
		return;
	}

	HpBar->SetActive(false);
}
