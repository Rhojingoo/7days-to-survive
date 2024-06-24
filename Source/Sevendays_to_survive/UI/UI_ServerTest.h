// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "UI_ServerTest.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API AUI_ServerTest : public AGameMode
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
};
