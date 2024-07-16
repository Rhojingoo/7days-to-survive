// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_ItemBox.h"

#include "STS/C_STSGlobalFunctions.h"
#include "Map/C_ItemPouch.h"
#include "Map/C_MapDataAsset.h"

// Sets default values
AC_ItemBox::AC_ItemBox()
{
}

// Called when the game starts or when spawned
void AC_ItemBox::BeginPlay()
{
	Super::BeginPlay();

	MapDataAsset = UC_STSGlobalFunctions::GetMapDataAsset();
	ItemPouchClass = MapDataAsset->GetItemPouchClass();
}

// Called every frame
void AC_ItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_ItemBox::PreDestroy()
{
	SpawnItems();
}

void AC_ItemBox::SpawnItems_Implementation()
{
	TArray<FC_ItemAndCount> DropItems = MapDataAsset->GetRandomDropItems();

	for (FC_ItemAndCount& ItemAndCount : DropItems)
	{
		AC_ItemPouch* ItemPouch = GetWorld()->SpawnActor<AC_ItemPouch>(ItemPouchClass.Get(), GetActorTransform());
		ItemPouch->SetItemAndCount(ItemAndCount.Item->Id, ItemAndCount.Count);
	}
}
