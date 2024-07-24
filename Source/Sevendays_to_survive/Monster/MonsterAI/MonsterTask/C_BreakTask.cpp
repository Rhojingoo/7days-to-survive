// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_BreakTask.h"

UC_BreakTask::UC_BreakTask()
{
}

EBTNodeResult::Type UC_BreakTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	if (false == Controller->IsValidLowLevel()) {
		return EBTNodeResult::Failed;
	}
	Controller->GetMCP()->Attack();
	return EBTNodeResult::Succeeded;
}

void UC_BreakTask::InitTask(UBehaviorTreeComponent* OwnerComp)
{
	Super::InitTask(OwnerComp);
}

void UC_BreakTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
