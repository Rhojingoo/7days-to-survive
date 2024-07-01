// Fill out your copyright notice in the Description page of Project Settings.


#include "STS/C_STSGlobalFunctions.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Global/C_MapPlayer.h"
#include "BuildingSystem/C_BuildingComponent.h"
#include "Inventory/C_InventoryComponent.h"
#include "Map/C_MapInteractionComponent.h"
#include "Engine/Light.h"
#include "Components/TimelineComponent.h"

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
