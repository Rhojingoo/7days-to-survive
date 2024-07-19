// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_ItemPouch.h"

#include "STS/C_STSGlobalFunctions.h"
#include "Inventory/C_InventoryComponent.h"
#include "Map/C_MapDataAsset.h"
#include "Map/UI/C_MapInteractionWidget.h"
#include "Map/C_MapInteractionComponent.h"

// Sets default values
AC_ItemPouch::AC_ItemPouch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	SetRootComponent(StaticMeshComponent);
}

void AC_ItemPouch::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

FC_ItemAndCount AC_ItemPouch::GetItemAndCount() const
{
	return ItemAndCount;
}

void AC_ItemPouch::SetItemAndCount_Implementation(FName _Id, int _Count)
{
	ItemAndCount.Item = UC_STSGlobalFunctions::FindItem(_Id);
	ItemAndCount.Count = _Count;
}

void AC_ItemPouch::MapInteract()
{
	UC_InventoryComponent* Inventory = UC_STSGlobalFunctions::GetInventoryComponent();
	Inventory->AddItem(ItemAndCount.Item, ItemAndCount.Count);
	
	//큇슬롯 창으로 Add해주기
	// 1. 퀵슬롯 창 생성하기
	// 2. 아이템 type이 무기인지 확인하기
	// 3. 큇슬롯 창에 AddItem 해주기

	//Enum* ItemCheck = StaticEnum<EItemType>();

	//if (true == EItemType::Weapon)
	//{
	//QuickSlot->AddItem()

	//}

	DestroyOnServer();
}

void AC_ItemPouch::ShowInteractionWidget()
{
	Super::ShowInteractionWidget();
	
	FVector Location = GetActorLocation() + FVector::UpVector * 50.0f;
	MapInteractionWidgetComponent->SetWorldLocation(Location);

	FString Text = ItemAndCount.Item->Name + TEXT(" × ") + FString::FromInt(ItemAndCount.Count);
	MapInteractionWidget->SetMessage(Text);
}

void AC_ItemPouch::HideInteractionWidget()
{
	Super::HideInteractionWidget();
}

// Called when the game starts or when spawned
void AC_ItemPouch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_ItemPouch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_ItemPouch::DestroyOnServer()
{
	UC_STSGlobalFunctions::GetMapInteractionComponent()->DestroyActor(this);
}

