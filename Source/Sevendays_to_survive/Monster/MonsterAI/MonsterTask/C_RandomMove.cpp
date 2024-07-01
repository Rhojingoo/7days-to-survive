// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_RandomMove.h"

UC_RandomMove::UC_RandomMove()
{
	NodeName = "Task_RandomVecterMove";
	bNotifyTick = true;
}

EBTNodeResult::Type UC_RandomMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	return EBTNodeResult::Type::InProgress;
}

void UC_RandomMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	FVector SelfVec = GetSelfLocationNoneZ(&OwnerComp);
	FVector RanVec = GetBlackBoard(&OwnerComp)->GetValueAsVector(*RandomVector);
	FVector Direction = (RanVec - SelfVec).GetSafeNormal();


	GetController(&OwnerComp)->GetMCP()->Move(Direction);

	float Vec = FVector::Dist(SelfVec, RanVec);

#ifdef WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("Self: %f"), SelfVec);
	UE_LOG(LogTemp, Warning, TEXT("Ran: %f"), RanVec);
	UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Vec);
#endif

	if (Vec < 300.f) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
