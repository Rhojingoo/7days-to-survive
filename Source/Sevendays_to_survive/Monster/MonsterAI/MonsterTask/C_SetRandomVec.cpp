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
    // �ݰ��� ������ ��� ���� ó��
    if (Radius < 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("Radius should be non-negative"));
        return Origin;
    }

    // �� ������ ���� ��ġ�� ����
    FVector RandomUnitVector = UKismetMathLibrary::RandomUnitVector();
    float RandomDistance = FMath::FRandRange(0.0f, Radius);

    // �������κ��� ���� ��ġ ��ȯ
    return Origin + RandomUnitVector * RandomDistance;
}
