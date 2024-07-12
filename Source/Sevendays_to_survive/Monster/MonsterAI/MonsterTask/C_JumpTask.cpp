// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_JumpTask.h"

UC_JumpTask::UC_JumpTask()
{
	//bNotifyTick = true;
	NodeName = "JumpTask";
}

EBTNodeResult::Type UC_JumpTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	if (true == Controller->GetMCP()->JumpCheck()) {
		Controller->GetMCP()->Jump();
		return EBTNodeResult::Type::Succeeded;
	}
	else {
		return EBTNodeResult::Type::Failed;
	}
}

void UC_JumpTask::InitTask(UBehaviorTreeComponent* OwnerComp)
{
	Super::InitTask(OwnerComp);
}

void UC_JumpTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	//AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	//AC_ZombieBase* Zombie = GetSelf(&OwnerComp);
	//bool IsJumping = GetController(&OwnerComp)->GetBlackboardComponent()->GetValueAsBool(*IsJump);

	//FVector ForwardVec = Zombie->GetActorForwardVector();
	//
	//if (Controller->GetMCP()->IsFalling() == true && IsJumping == true) {
	//	Controller->GetMCP()->AddLocation(ForwardVec);
	//	return;
	//}
	//else {
	//	Controller->GetBlackboardComponent()->SetValueAsBool(*IsJump, false);
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//}
}
