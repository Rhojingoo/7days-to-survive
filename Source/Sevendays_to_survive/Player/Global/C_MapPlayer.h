// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Global/C_GlobalPlayer.h"
#include "C_MapPlayer.generated.h"

class UC_BuildingComponent;
class UC_InventoryComponent;
class UC_MapInteractionComponent;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_MapPlayer : public AC_GlobalPlayer
{
	GENERATED_BODY()

public:
	AC_MapPlayer();



protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

protected:
	UPROPERTY(Category = "Contents | Map", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UC_BuildingComponent* BuildingComponent = nullptr;

	UPROPERTY(Category = "Contents | Map", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UC_InventoryComponent* InventoryComponent = nullptr;

	UPROPERTY(Category = "Contents | Map", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UC_MapInteractionComponent* MapInteractionComp = nullptr;
};
