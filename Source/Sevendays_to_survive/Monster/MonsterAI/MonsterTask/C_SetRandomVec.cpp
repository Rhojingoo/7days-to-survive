// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_SetRandomVec.h"
#include <Kismet/KismetMathLibrary.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterData/MonsterDataRow.h"
#include <NavigationSystem.h>
#include "NavigationPath.h"


UC_SetRandomVec::UC_SetRandomVec()
{
	NodeName = "Task_SetRandomVec";
}

EBTNodeResult::Type UC_SetRandomVec::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	if (Controller->IsValidLowLevel() == false) {
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = GetBlackBoard(&OwnerComp);
	if (false == BlackBoard->IsValidLowLevel()) {
		return EBTNodeResult::Failed;
	}
	FVector Vec = GetRandomVectorInRadius(GetSelf(&OwnerComp)->GetActorLocation(), 2000.f);
	Vec.Z = 0;
	GetBlackBoard(&OwnerComp)->SetValueAsVector(*RandomVector, Vec);

	UMonsterDataObject* Data = Controller->GetMCP()->GetData();
	if (true == IsPerceptionUpdated(Controller)) {
		Data->RemovePath();
		return EBTNodeResult::Succeeded;
	}

	FVector SelfVec = GetSelfLocationNoneZ(&OwnerComp);
	FVector RanVec = GetBlackBoard(&OwnerComp)->GetValueAsVector(*RandomVector);

	float Dist = FVector::Distance(RanVec, SelfVec);

	if (Dist <= 1500) {
		return EBTNodeResult::Succeeded;
	}

	if (true == Data->PathIsEmpty()) {
		SetPath(SelfVec, RanVec, Data, BlackBoard);
		return EBTNodeResult::Succeeded;
	}
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
	float RandomDistance = FMath::FRandRange(1000.f, Radius);

	// 원점으로부터 랜덤 위치 반환
	return Origin + RandomUnitVector * RandomDistance;
}


bool UC_SetRandomVec::SetPath(FVector _MyLocation, FVector _TargetLocation, UMonsterDataObject* _Data, UBlackboardComponent* _BBC)
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (true == NavSystem->IsValidLowLevel())
	{
		UNavigationPath* NavPath = NavSystem->FindPathToLocationSynchronously(GetWorld(), _MyLocation, _TargetLocation);

		if (NavPath && NavPath->IsValid())
		{
			_Data->SetPath(NavPath->PathPoints);
			//_BBC->SetValueAsVector(*StartLocation, NavPath->PathPoints[0]);
			_Data->PathHeadRemove();  //이걸 삭제하는 이유는 맨 첫번째 위치는 selflocation의 위치 즉 처음 시작 위치이다.
			return true;
		}
	}
	return false;
}
