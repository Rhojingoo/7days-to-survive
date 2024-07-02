// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "C_7Days_Play_GameMode.generated.h"

class UTimelineComponent;
class ALight;
/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_7Days_Play_GameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsServer = false;

};
