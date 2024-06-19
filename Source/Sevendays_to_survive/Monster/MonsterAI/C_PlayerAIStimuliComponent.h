// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "C_PlayerAIStimuliComponent.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_PlayerAIStimuliComponent : public UAIPerceptionStimuliSourceComponent
{
	GENERATED_BODY()

public:

	bool Init();
};
