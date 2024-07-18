﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "STS/C_STSGlobalFunctions.h"

#include "Components/TimelineComponent.h"
#include "Engine/Light.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Global/C_MapPlayer.h"
#include "BuildingSystem/C_BuildingComponent.h"
#include "Inventory/C_InventoryComponent.h"
#include "Map/C_MapInteractionComponent.h"
#include "STS/C_STSInstance.h"
#include "Map/C_MapDataAsset.h"
#include "UI/C_UI_InGameHUD.h"
#include "UI/Inventory/C_UI_InventoryCore.h"


UC_BuildingComponent* UC_STSGlobalFunctions::GetBuildingComponent()
{
    return GetMapPlayerCharacter()->GetComponentByClass<UC_BuildingComponent>();
}

UC_InventoryComponent* UC_STSGlobalFunctions::GetInventoryComponent()
{
    return GetMapPlayerCharacter()->GetComponentByClass<UC_InventoryComponent>();
}

UC_MapInteractionComponent* UC_STSGlobalFunctions::GetMapInteractionComponent()
{
    return GetMapPlayerCharacter()->GetComponentByClass<UC_MapInteractionComponent>();
}

AC_MapPlayer* UC_STSGlobalFunctions::GetMapPlayerCharacter()
{
    UWorld* World = GEngine->GameViewport->GetWorld();
    return Cast<AC_MapPlayer>(UGameplayStatics::GetPlayerPawn(World, 0));
}

UC_MapDataAsset* UC_STSGlobalFunctions::GetMapDataAsset()
{
    UWorld* World = GEngine->GameViewport->GetWorld();
    UC_STSInstance* Inst = World->GetGameInstanceChecked<UC_STSInstance>();
    return Inst->GetMapDataAsset();
}

void UC_STSGlobalFunctions::Day_And_Night_Cycle(ALight* _DirectionLight)
{
    if (nullptr == _DirectionLight)
    {
        int a = 0;
        return;
    }

    TObjectPtr<class ULightComponent> LightComponent = _DirectionLight->GetLightComponent();

    if (nullptr == LightComponent)
    {
        int a = 0;
        return;
    }




    LightComponent;   
}

const UC_Item* UC_STSGlobalFunctions::FindItem(FName _Id)
{
    return GetMapDataAsset()->FindItem(_Id);
}

AC_UI_InGameHUD* UC_STSGlobalFunctions::GetInGameHUD()
{
    UWorld* World = GEngine->GameViewport->GetWorld();
    return Cast<AC_UI_InGameHUD>(UGameplayStatics::GetPlayerController(World, 0)->GetHUD());
}

UC_UI_InventoryCore* UC_STSGlobalFunctions::GetInventoryCore()
{
    AC_UI_InGameHUD* InGameHUD = GetInGameHUD();
    return InGameHUD->GetInventoryCore();
}