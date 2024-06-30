// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_TaskMonsterChase.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"

UC_TaskMonsterChase::UC_TaskMonsterChase()
{
	NodeName = "MonsterChase";
}

EBTNodeResult::Type UC_TaskMonsterChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	if (!IsValid(Controller)) {
		UE_LOG(LogTemp, Warning, TEXT("MonsterController is Not Work BTTESK %d  %s"), __LINE__, ANSI_TO_TCHAR(__FUNCTION__));
		return EBTNodeResult::Failed;
	}
	if (Controller->GetIsFind()) {
		APawn* Pawn = Cast<APawn>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));
		Controller->MoveToLocation(Pawn->GetActorLocation());
		GetSelf(&OwnerComp)->SetState(MonsterEnum::Move);
		return EBTNodeResult::Succeeded;
	}

	else {
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Type::Failed;
}

void UC_TaskMonsterChase::InitTask(UBehaviorTreeComponent* OwnerComp)
{
	Super::InitTask(OwnerComp);
}
