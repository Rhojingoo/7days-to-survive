// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_SetRandomVec.h"
#include <Kismet/KismetMathLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"

UC_SetRandomVec::UC_SetRandomVec()
{
	NodeName = "Task_SetRandomVec";
}

EBTNodeResult::Type UC_SetRandomVec::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	FVector Vec = GetRandomVectorInRadius(GetSelf(&OwnerComp)->GetActorLocation(), 500.f);
	Vec.Z = 0;
	GetBlackBoard(&OwnerComp)->SetValueAsVector(*RandomVector, Vec);
	return EBTNodeResult::Type::Succeeded;
}

FVector UC_SetRandomVec::GetRandomVectorInRadius(const FVector& Origin, float Radius)
{
	// 구 내부의 랜덤 위치를 생성
	FVector RandomUnitVector = UKismetMathLibrary::RandomUnitVector();
	float RandomDistance = FMath::FRandRange(0.0f, Radius);

	return Origin + RandomUnitVector * RandomDistance;
}