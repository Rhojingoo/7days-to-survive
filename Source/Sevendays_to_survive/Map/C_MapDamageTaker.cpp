// Fill out your copyright notice in the Description page of Project Settings.

#include "Map/C_MapDamageTaker.h"

#include "Net/UnrealNetwork.h"
#include "STS/C_STSMacros.h"
#include "UI/C_HealthBar.h"
#include "Kismet/GameplayStatics.h"

AC_MapDamageTaker::AC_MapDamageTaker()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SMComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM Component"));
	SetRootComponent(SMComponent);

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	HpBar->SetupAttachment(SMComponent);
}

void AC_MapDamageTaker::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AC_MapDamageTaker, Hp);
}

float AC_MapDamageTaker::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	ReceiveDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return DamageAmount;
}

// Called when the game starts or when spawned
void AC_MapDamageTaker::BeginPlay()
{
	Super::BeginPlay();
	
	Hp = MaxHp;

	HpBarWidget = Cast<UC_HealthBar>(HpBar->GetWidget());

	if (nullptr == HpBarWidget)
	{
		STS_FATAL("[%s] HpBarWidget is NULL.", __FUNCTION__);
		return;
	}

	HideHpBar();
}

// Called every frame
void AC_MapDamageTaker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AC_MapDamageTaker::UpdateHpBar()
{
	if (Hp <= 0)
	{
		STS_LOG("UpdateHpBar failed. Given BuildingPart is already destroyed.", 0);
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

void AC_MapDamageTaker::HideHpBar()
{
	HpBarWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AC_MapDamageTaker::ReceiveDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Hp -= DamageAmount;

	if (Hp <= 0.0f)
	{
		PreDestroy();
		Destroy();
	}
}
