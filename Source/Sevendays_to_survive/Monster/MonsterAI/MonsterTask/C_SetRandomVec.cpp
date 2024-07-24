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
    // 반경이 음수인 경우 예외 처리
    if (Radius < 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("Radius should be non-negative"));
        return Origin;
    }

    // 구 내부의 랜덤 위치를 생성
    FVector RandomUnitVector = UKismetMathLibrary::RandomUnitVector();
    float RandomDistance = FMath::FRandRange(20.0f, Radius);

    // 원점으로부터 랜덤 위치 반환
    return Origin + RandomUnitVector * RandomDistance;
}
