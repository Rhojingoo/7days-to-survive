// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_MapInteractable.h"

#include "Map/UI/C_MapInteractionWidget.h"

AC_MapInteractable::AC_MapInteractable()
{
    MapInteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget Component"));
    MapInteractionWidgetComponent->SetupAttachment(GetRootComponent());
}

void AC_MapInteractable::BeginPlay()
{
    Super::BeginPlay();

    MapInteractionWidget = Cast<UC_MapInteractionWidget>(MapInteractionWidgetComponent->GetWidget());
    MapInteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
}

