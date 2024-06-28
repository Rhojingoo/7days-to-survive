// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Global/C_MapPlayer.h"

#include "BuildingSystem/C_BuildingComponent.h"
#include "Inventory/C_InventoryComponent.h"

#include "Map/C_MapInteractionComponent.h"

AC_MapPlayer::AC_MapPlayer()
{
	static ConstructorHelpers::FClassFinder<UC_BuildingComponent> BpBuildingComponentAsset(TEXT("/Script/Engine.Blueprint'/Game/Level/Main_Level/MapContent/BP/BP_BuildingComponent.BP_BuildingComponent_C'"));
	if (true == BpBuildingComponentAsset.Succeeded())
	{
		TSubclassOf<UActorComponent> BpClass = BpBuildingComponentAsset.Class;
		BuildingComponent = Cast<UC_BuildingComponent>(CreateDefaultSubobject(TEXT("Building Component"), UC_BuildingComponent::StaticClass(), BpClass.Get(), true, false));
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Can't find BP Building Component"));
	}

	static ConstructorHelpers::FClassFinder<UC_InventoryComponent> BpInventoryComponentAsset(TEXT("/Script/Engine.Blueprint'/Game/Level/Main_Level/MapContent/BP/BP_InventoryComponent.BP_InventoryComponent_C'"));
	if (true == BpInventoryComponentAsset.Succeeded())
	{
		TSubclassOf<UActorComponent> BpClass = BpInventoryComponentAsset.Class;
		InventoryComponent = Cast<UC_InventoryComponent>(CreateDefaultSubobject(TEXT("Inventory Component"), UC_InventoryComponent::StaticClass(), BpClass.Get(), true, false));
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Can't find BP Inventory Component"));
	}

	static ConstructorHelpers::FClassFinder<UC_MapInteractionComponent> BpMapInteractionComponentAsset(TEXT("/Script/Engine.Blueprint'/Game/Level/Main_Level/MapContent/BP/BP_MapInteractionComponent.BP_MapInteractionComponent_C'"));
	if (true == BpMapInteractionComponentAsset.Succeeded())
	{
		TSubclassOf<UActorComponent> BpClass = BpMapInteractionComponentAsset.Class;
		MapInteractionComp = Cast<UC_MapInteractionComponent>(CreateDefaultSubobject(TEXT("Map Interaction Component"), UC_MapInteractionComponent::StaticClass(), BpClass.Get(), true, false));
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Can't find BP Map Interaction Component"));
	}
}

void AC_MapPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AC_MapPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

