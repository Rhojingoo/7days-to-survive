// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_ItemBox.h"

#include "Net/UnrealNetwork.h"
#include "STS/C_STSMacros.h"
#include "STS/C_STSGlobalFunctions.h"
#include "UI/C_HealthBar.h"
#include "Kismet/GameplayStatics.h"
#include "Map/C_ItemPouch.h"
#include "Map/C_MapDataAsset.h"

// Sets default values
AC_ItemBox::AC_ItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SMComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM Component"));
	SetRootComponent(SMComponent);

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	HpBar->SetupAttachment(SMComponent);
}

// Called when the game starts or when spawned
void AC_ItemBox::BeginPlay()
{
	Super::BeginPlay();

	Hp = MaxHp;

	HpBarWidget = Cast<UC_HealthBar>(HpBar->GetWidget());

	if (nullptr == HpBarWidget)
	{
		STS_FATAL("[%s] HpBarWidget is NULL.", __FUNCTION__);
		return;
	}

	UC_MapDataAsset* MapDataAsset = UC_STSGlobalFunctions::GetMapDataAsset();
	ItemPouchClass = MapDataAsset->GetItemPouchClass();

	HideHpBar();
}

// Called every frame
void AC_ItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_ItemBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AC_ItemBox, Hp);
}

float AC_ItemBox::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	ReceiveDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return DamageAmount;
}

void AC_ItemBox::ReceiveDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Hp -= DamageAmount;

	if (Hp <= 0.0f)
	{
		SpawnItems();
		Destroy();
	}
}

void AC_ItemBox::UpdateHpBar()
{
	if (Hp <= 0)
	{
		STS_LOG("UpdateHpBar failed. Given ItemBox is already destroyed.", 0);
		return;
	}

	if (false == HpBarWidget->IsVisible())
	{
		HpBarWidget->SetVisibility(ESlateVisibility::Visible);
	}

	FVector InstLocation = GetActorLocation() + FVector::UpVector * HpBarHeight;
	FVector DrawLocation = InstLocation;

	// HpBar 갱신
	HpBar->SetWorldLocation(DrawLocation);
	HpBarWidget->SetCurHealth(Hp);
	HpBarWidget->SetMaxHealth(MaxHp);
}

void AC_ItemBox::HideHpBar()
{
	HpBarWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AC_ItemBox::SpawnItems_Implementation()
{
	for (TPair<FName, int>& ItemAndCount : DropItems)
	{
		AC_ItemPouch* ItemPouch = GetWorld()->SpawnActor<AC_ItemPouch>(ItemPouchClass.Get(), GetActorTransform());
		ItemPouch->SetItemAndCount(ItemAndCount.Key, ItemAndCount.Value);
	}
}
