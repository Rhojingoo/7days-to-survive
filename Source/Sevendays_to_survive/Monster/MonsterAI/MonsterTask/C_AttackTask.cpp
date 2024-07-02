// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_AttackTask.h"

EBTNodeResult::Type UC_AttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GetController(&OwnerComp)->GetMCP()->Attack();

	return EBTNodeResult::Type();
}
