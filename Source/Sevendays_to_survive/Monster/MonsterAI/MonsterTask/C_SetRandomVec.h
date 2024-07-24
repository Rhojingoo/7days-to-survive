// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterAI/MonsterTask/C_BlackBoardBase.h"
#include "C_SetRandomVec.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_SetRandomVec : public UC_BlackBoardBase
{
	GENERATED_BODY()
	
public:
	UC_SetRandomVec();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	FVector GetRandomVectorInRadius(const FVector& Origin, float Radius);

	bool SetPath(FVector _MyLocation, FVector _TargetLocation, UMonsterDataObject* _Data, UBlackboardComponent* _BBC);

};
