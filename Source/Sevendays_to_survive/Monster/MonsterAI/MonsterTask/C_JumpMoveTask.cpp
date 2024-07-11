// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_JumpMoveTask.h"

UC_JumpMoveTask::UC_JumpMoveTask()
{
	bNotifyTick = true;
	NodeName = "JumpMoveTask";
}

EBTNodeResult::Type UC_JumpMoveTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	if (Controller->GetMCP()->IsFalling() == true) {
		return EBTNodeResult::Type::InProgress;
	}
	else {
		return EBTNodeResult::Type::Failed;
	}
}

void UC_JumpMoveTask::InitTask(UBehaviorTreeComponent* OwnerComp)
{
	Super::InitTask(OwnerComp);
}

void UC_JumpMoveTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	AC_ZombieBase* Zombie = GetSelf(&OwnerComp);
	FVector ForwardVec = Zombie->GetActorForwardVector();

	if (Controller->GetMCP()->IsFalling() == true) {
		Controller->GetMCP()->AddLocation(ForwardVec);
		return;
	}
	else {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
