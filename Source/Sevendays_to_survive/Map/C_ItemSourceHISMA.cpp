// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_ItemSourceHISMA.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "STS/C_STSInstance.h"
#include "Map/C_MapDataAsset.h"
#include "Map/C_ItemSourceTableRow.h"
#include "Map/C_Items.h"
#include "Player/Global/C_GlobalPlayer.h"
#include "Inventory/C_InventoryComponent.h"
#include "STS/C_STSMacros.h"

AC_ItemSourceHISMA::AC_ItemSourceHISMA()
{
	PrimaryActorTick.bCanEverTick = true;

	HISMComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HierarchicalInstancedStaticMesh"));
	SetRootComponent(HISMComponent);
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
	}
}

void AC_ItemSourceHISMA::GainDropItems()
{
	AC_GlobalPlayer* PlayerCharacter = Cast<AC_GlobalPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (nullptr == PlayerCharacter)
	{
		STS_FATAL("[%s] PlayerCharacter is NULL.", __FUNCTION__);
	}

	UC_InventoryComponent* InventoryComponent = PlayerCharacter->GetComponentByClass<UC_InventoryComponent>();
	if (nullptr == InventoryComponent)
	{
		STS_FATAL("[%s] InventoryComponent is NULL.", __FUNCTION__);
	}

	for (FC_ItemAndCount& DropItem : DropItems)
	{
		InventoryComponent->AddItem(DropItem.Item, DropItem.Count);
		STS_LOG("got %d %ss.", DropItem.Count, *DropItem.Item->Name);
		// TODO: 아이템 획득을 서버에 알린다.
	}
}