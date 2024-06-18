// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_BlackBoardBase.h"

UC_BlackBoardBase::UC_BlackBoardBase()
{
}

EBTNodeResult::Type UC_BlackBoardBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	int a = 0;
	return EBTNodeResult::Type();
}

void UC_BlackBoardBase::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UC_BlackBoardBase::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
}
