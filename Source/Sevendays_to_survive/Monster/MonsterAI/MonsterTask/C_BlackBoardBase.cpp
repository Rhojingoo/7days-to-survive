// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_BlackBoardBase.h"
#include "Kismet/GameplayStatics.h"


UC_BlackBoardBase::UC_BlackBoardBase()
{
}

EBTNodeResult::Type UC_BlackBoardBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	return EBTNodeResult::Type();
}

void UC_BlackBoardBase::InitTask(UBehaviorTreeComponent* OwnerComp)
{
}


UBlackboardComponent* UC_BlackBoardBase::GetBlackBoard(UBehaviorTreeComponent* OwnerComp)
{
	return OwnerComp->GetBlackboardComponent();
}

AC_ZombieBase* UC_BlackBoardBase::GetSelf(UBehaviorTreeComponent* OwnerComp)
{
	return Cast<AC_ZombieBase>(GetBlackBoard(OwnerComp)->GetValueAsObject("SelfActor"));
}

AC_MonsterAIBase* UC_BlackBoardBase::GetController(UBehaviorTreeComponent* OwnerComp)
{
	return Cast< AC_MonsterAIBase>(OwnerComp->GetOwner());
}

FVector UC_BlackBoardBase::GetSelfLocationNoneZ(UBehaviorTreeComponent* OwnerComp)
{
	FVector Vec = GetSelf(OwnerComp)->GetActorLocation();
	Vec.Z = 0;
	return Vec;
}

FVector UC_BlackBoardBase::GetSelfLocation(UBehaviorTreeComponent* OwnerComp)
{
	FVector Vec = GetSelf(OwnerComp)->GetComponentLocation();
	return Vec;
}

FVector UC_BlackBoardBase::GetSelfVelocity(UBehaviorTreeComponent* OwnerComp)
{
	return GetSelf(OwnerComp)->GetVelocity();
}

bool UC_BlackBoardBase::IsPerceptionUpdated(AC_MonsterAIBase* _Controller)
{
	if (true == _Controller->GetIsFind()) {
		return true;;
	}
	else if (true == _Controller->GetIsSound()) {
		return true;
	}
	return false;
}
