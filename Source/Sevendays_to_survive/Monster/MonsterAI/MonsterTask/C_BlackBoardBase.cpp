// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_BlackBoardBase.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"

UC_BlackBoardBase::UC_BlackBoardBase()
{
}

EBTNodeResult::Type UC_BlackBoardBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (IsInit == false) {
		IsInit = true;
		InitTask(&OwnerComp);
	}
	return EBTNodeResult::Type();
}

void UC_BlackBoardBase::InitTask(UBehaviorTreeComponent* OwnerComp)
{
	TaskController = Cast<AC_MonsterAIBase>(OwnerComp->GetOwner());
	BlackboardComp = OwnerComp->GetBlackboardComponent();
}
