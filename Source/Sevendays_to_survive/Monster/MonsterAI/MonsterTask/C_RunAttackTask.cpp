// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_RunAttackTask.h"

UC_RunAttackTask::UC_RunAttackTask()
{
	NodeName = "RunAttackTask";
}

EBTNodeResult::Type UC_RunAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UObject* Object = GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor);

	if (Object->IsValidLowLevel()) {
		return EBTNodeResult::Type::InProgress;
	}
	else {
		return EBTNodeResult::Type::Failed;
	}
}

void UC_RunAttackTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return;
}
