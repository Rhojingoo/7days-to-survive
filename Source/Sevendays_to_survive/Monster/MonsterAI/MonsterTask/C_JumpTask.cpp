// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_JumpTask.h"

UC_JumpTask::UC_JumpTask()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UC_JumpTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	return EBTNodeResult::Type();
}

void UC_JumpTask::InitTask(UBehaviorTreeComponent* OwnerComp)
{
	Super::InitTask(OwnerComp);
}

void UC_JumpTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	bool IsJumping = GetController(&OwnerComp)->GetBlackboardComponent()->GetValueAsBool(*IsJump);

	if (IsJumping == false) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
