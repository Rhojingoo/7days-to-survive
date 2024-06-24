// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "C_TaskMonsterPatrol.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_TaskMonsterPatrol : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	void ExampleUsage();
	FVector GetRandomVectorInRadius(const FVector& Origin, float Radius);
};
