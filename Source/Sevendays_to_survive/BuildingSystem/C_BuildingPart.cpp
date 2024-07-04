// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSystem/C_BuildingPart.h"

#include "Net/UnrealNetwork.h"
#include "STS/C_STSMacros.h"
#include "UI/C_HealthBar.h"
#include "Kismet/GameplayStatics.h"

AC_BuildingPart::AC_BuildingPart()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
    HpBar->SetupAttachment(GetRootComponent());
}

void AC_BuildingPart::BeginPlay()
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

void AC_BuildingPart::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AC_BuildingPart, Hp);
}

float AC_BuildingPart::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    ReceiveDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    return DamageAmount;
}

void AC_BuildingPart::ReceiveDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Hp -= DamageAmount;

    if (Hp <= 0.0f)
    {
        Destroy();
    }
}

void AC_BuildingPart::UpdateHpBar()
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

void AC_BuildingPart::HideHpBar()
{
	HpBarWidget->SetVisibility(ESlateVisibility::Collapsed);
}
