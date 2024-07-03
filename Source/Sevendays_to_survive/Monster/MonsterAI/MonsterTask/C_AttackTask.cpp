// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_AttackTask.h"

UC_AttackTask::UC_AttackTask() {
	NodeName = "AttackTask";
	bNotifyTick = true;
}


EBTNodeResult::Type UC_AttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));
	if (Target->IsValidLowLevel()) {
		return EBTNodeResult::Type::InProgress;
	}

	else {
		return EBTNodeResult::Type::Failed;
	}
}

void UC_AttackTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AC_MonsterAIBase* Controller = GetController(&OwnerComp);

	AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));
	FVector TargetLocation = Target->GetActorLocation();
	TargetLocation.Z = 0;

	FVector SelfLocation = GetSelfLocationNoneZ(&OwnerComp);

	float Vec = FVector::Dist(SelfLocation, TargetLocation);
	GetController(&OwnerComp)->GetMCP()->Move(Target->GetActorLocation() - SelfLocation);
	//if (Vec < 100.f) {
	//	GetController(&OwnerComp)->GetMCP()->Attack();
	//	return;
	//}
	//else if (Vec < 200.f) {
	//	GetController(&OwnerComp)->GetMCP()->RunAttack();
	//	GetController(&OwnerComp)->GetMCP()->Move(Target->GetActorLocation() - SelfLocation);
	//	return;
	//}
	//else {
	if (Vec < 100.f) {
		GetController(&OwnerComp)->GetMCP()->Attack();
		return;
	}
	//return;
	//}
	return;
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return;
}
