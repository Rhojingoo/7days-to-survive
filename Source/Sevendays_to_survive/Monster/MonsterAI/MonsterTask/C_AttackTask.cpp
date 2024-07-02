// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_AttackTask.h"

UC_AttackTask::UC_AttackTask() {
	NodeName = "AttackTask";
	bNotifyTick = true;
}


EBTNodeResult::Type UC_AttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GetController(&OwnerComp)->GetMCP()->Attack();

	return EBTNodeResult::Type::InProgress;
}

void UC_AttackTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AC_MonsterAIBase* Controller = GetController(&OwnerComp);

	AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));
	FVector TargetLocation = Target->GetActorLocation();
	TargetLocation.Z = 0;

	FVector SelfLocation = GetSelfLocationNoneZ(&OwnerComp);

	GetController(&OwnerComp)->GetMCP()->Move(Target->GetActorLocation() - SelfLocation);
	float Vec = FVector::Dist(SelfLocation, TargetLocation);
	if (Vec < 100.f) {
		GetController(&OwnerComp)->GetMCP()->Attack();
	}


	//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return;
}
