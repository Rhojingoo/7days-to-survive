// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_MonsterWait.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"

UC_MonsterWait::UC_MonsterWait()
{
	NodeName = "MonsterWait";
	bNotifyTick = true;
}

EBTNodeResult::Type UC_MonsterWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!IsValid(TaskController)) {
		UE_LOG(LogTemp, Warning, TEXT("MonsterController is Not Work BTTESK %d  %s"), __LINE__, ANSI_TO_TCHAR(__FUNCTION__));
		return EBTNodeResult::Failed;
	}

	if (true == TaskController->GetIsFind()) {
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::InProgress;
}

void UC_MonsterWait::InitTask(UBehaviorTreeComponent* OwnerComp)
{
	Super::InitTask(OwnerComp);
}

void UC_MonsterWait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (true == TaskController->GetIsFind()) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	float Time = BlackboardComp->GetValueAsFloat(*WaitTimeName);
	if (Waiting > Time) {
		BlackboardComp->SetValueAsFloat(*WaitTimeName, Time + DeltaSeconds);
	}
	else {
		BlackboardComp->SetValueAsFloat(*WaitTimeName, 0.f);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
}
