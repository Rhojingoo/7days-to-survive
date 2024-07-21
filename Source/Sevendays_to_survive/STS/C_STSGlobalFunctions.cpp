// Fill out your copyright notice in the Description page of Project Settings.


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
#include "Map/C_MapDataMemory.h"
#include "UI/C_UI_InGameHUD.h"
#include "UI/Inventory/C_UI_InventoryCore.h"


UC_BuildingComponent* UC_STSGlobalFunctions::GetBuildingComponent(const UObject* WorldContextObject)
{
    return GetMapPlayerCharacter(WorldContextObject)->GetComponentByClass<UC_BuildingComponent>();
}

UC_InventoryComponent* UC_STSGlobalFunctions::GetInventoryComponent(const UObject* WorldContextObject)
{
    return GetMapPlayerCharacter(WorldContextObject)->GetComponentByClass<UC_InventoryComponent>();
}

UC_MapInteractionComponent* UC_STSGlobalFunctions::GetMapInteractionComponent(const UObject* WorldContextObject)
{
    return GetMapPlayerCharacter(WorldContextObject)->GetComponentByClass<UC_MapInteractionComponent>();
}

AC_MapPlayer* UC_STSGlobalFunctions::GetMapPlayerCharacter(const UObject* WorldContextObject)
{
    return Cast<AC_MapPlayer>(UGameplayStatics::GetPlayerPawn(WorldContextObject, 0));
}

UC_STSInstance* UC_STSGlobalFunctions::GetInst(const UObject* WorldContextObject)
{
    return Cast<UC_STSInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
}

UC_MapDataAsset* UC_STSGlobalFunctions::GetMapDataAsset(const UObject* WorldContextObject)
{
    return GetInst(WorldContextObject)->GetMapDataAsset();
}

UC_MapDataMemory* UC_STSGlobalFunctions::GetMapDataMemory(const UObject* WorldContextObject)
{
    return GetInst(WorldContextObject)->GetMapDataMemory();
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

const UC_Item* UC_STSGlobalFunctions::FindItem(const UObject* WorldContextObject, FName _Id)
{
    return GetMapDataMemory(WorldContextObject)->FindItem(_Id);
}

AC_UI_InGameHUD* UC_STSGlobalFunctions::GetInGameHUD(const UObject* WorldContextObject)
{
    return Cast<AC_UI_InGameHUD>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetHUD());
}

UC_UI_InventoryCore* UC_STSGlobalFunctions::GetInventoryCore(const UObject* WorldContextObject)
{
    AC_UI_InGameHUD* InGameHUD = GetInGameHUD(WorldContextObject);
    return InGameHUD->GetInventoryCore();
}

UC_UI_QuickSlot* UC_STSGlobalFunctions::GetQuickSlotWidget(const UObject* WorldContextObject)
{
    AC_UI_InGameHUD* InGameHUD = GetInGameHUD(WorldContextObject);
    return InGameHUD->GetQuickSlotWidget();
}
