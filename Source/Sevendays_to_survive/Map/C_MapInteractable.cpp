// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_MapInteractable.h"

#include "Map/UI/C_MapInteractionWidget.h"

AC_MapInteractable::AC_MapInteractable()
{
    InteractionWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget Component"));
    InteractionWidgetComponent->SetupAttachment(GetRootComponent());
}

void AC_MapInteractable::BeginPlay()
{
    Super::BeginPlay();

    InteractionWidget = Cast<UC_MapInteractionWidget>(InteractionWidgetComponent->GetWidget());
}

