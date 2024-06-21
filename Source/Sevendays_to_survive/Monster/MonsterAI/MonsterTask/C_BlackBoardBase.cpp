// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_BlackBoardBase.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"

UC_BlackBoardBase::UC_BlackBoardBase()
{
	NodeName = "BaseTask";
}

EBTNodeResult::Type UC_BlackBoardBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AC_MonsterAIBase* MonsterController = Cast<AC_MonsterAIBase>(OwnerComp.GetOwner());

	if (!IsValid(MonsterController)) {
		UE_LOG(LogTemp, Warning, TEXT("MonsterController is Not Work BTTESK %d  %s"), __LINE__, ANSI_TO_TCHAR(__FUNCTION__));
	}
	if (MonsterController->GetIsFind()) {
		InitTask(&OwnerComp);
		MonsterController->MoveToLocation(TargetActor->GetActorLocation());
	}

	else {

	}
	return EBTNodeResult::Failed;
}


void UC_BlackBoardBase::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UC_BlackBoardBase::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
}

void UC_BlackBoardBase::InitTask(UBehaviorTreeComponent* OwnerComp)
{
	if (nullptr == TargetActor) {
	TargetActor = Cast<AActor>(OwnerComp->GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	}
}
