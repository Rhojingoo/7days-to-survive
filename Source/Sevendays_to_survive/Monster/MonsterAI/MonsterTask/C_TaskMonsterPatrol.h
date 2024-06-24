// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "C_BlackBoardBase.h"
#include "C_TaskMonsterPatrol.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_TaskMonsterPatrol : public UC_BlackBoardBase
{
	GENERATED_BODY()
	
public:
	UC_TaskMonsterPatrol();

	EBTNodeResult::Type PatrolMove(class AC_MonsterAIBase* _MonsterController);
	FVector GetRandomVectorInRadius(const FVector& Origin, float Radius);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY()
	FVector RandomVector = FVector::ZeroVector;

	void InitTask(UBehaviorTreeComponent* OwnerComp) override;
};


