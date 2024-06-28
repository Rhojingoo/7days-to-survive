// Fill out your copyright notice in the Description page of Project Settings.


#include "STS/C_STSGlobalFunctions.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Global/C_MapPlayer.h"
#include "BuildingSystem/C_BuildingComponent.h"
#include "Inventory/C_InventoryComponent.h"
#include "Map/C_MapInteractionComponent.h"

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
