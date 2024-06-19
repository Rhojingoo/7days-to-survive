// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_BlackBoardBase.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UC_BlackBoardBase::UC_BlackBoardBase()
{
	NodeName = "SetTargetActor";
}

EBTNodeResult::Type UC_BlackBoardBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) {
		UBlackboardComponent* BBC = OwnerComp.GetBlackboardComponent();
		BBC->SetValueAsObject(TEXT("TargetActor"), Pawn);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

void UC_BlackBoardBase::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UC_BlackBoardBase::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
}
