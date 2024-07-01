// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_Levels/C_7Days_Play_GameMode.h"
#include "Components/DirectionalLightComponent.h"
#include "Engine/Light.h"
#include "Components/TimelineComponent.h"

void AC_7Days_Play_GameMode::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = true;
	Super::BeginPlay();

	DayNight_Timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DayNight_Timeline"));

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/MyCurve.MyCurve'"));
	if (Curve.Succeeded())
	{
		FloatCurve = Curve.Object;
	}
}

void AC_7Days_Play_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

