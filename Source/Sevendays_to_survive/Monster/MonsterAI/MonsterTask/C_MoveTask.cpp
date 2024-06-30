// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_MoveTask.h"

UC_MoveTask::UC_MoveTask()
{
	//bNotifyTick = true;
}

EBTNodeResult::Type UC_MoveTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBC = GetBlackBoard(&OwnerComp);
	FVector Vec = BBC->GetValueAsVector(*TargetVector);
	GetSelf(&OwnerComp)->Move(Vec);

	return EBTNodeResult::Type::Succeeded;
}

void UC_MoveTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

