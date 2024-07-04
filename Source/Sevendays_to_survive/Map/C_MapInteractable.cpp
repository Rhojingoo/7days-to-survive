// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_MapInteractable.h"

#include "Map/UI/C_MapInteractionWidget.h"

AC_MapInteractable::AC_MapInteractable()
{
    bReplicates = true;

    MapInteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget Component"));
    MapInteractionWidgetComponent->SetupAttachment(GetRootComponent());

}

void AC_MapInteractable::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    //DOREPLIFETIME(AC_MapInteractable, VariableName);
}

void AC_MapInteractable::ShowInteractionWidget()
{
    MapInteractionWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void AC_MapInteractable::HideInteractionWidget()
{
    MapInteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AC_MapInteractable::BeginPlay()
{
    Super::BeginPlay();

    MapInteractionWidget = Cast<UC_MapInteractionWidget>(MapInteractionWidgetComponent->GetWidget());
    MapInteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
}

