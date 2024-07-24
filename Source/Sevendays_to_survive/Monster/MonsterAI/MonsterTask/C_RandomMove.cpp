// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_RandomMove.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include <NavigationSystem.h>
#include "NavigationPath.h"
#include "Monster/MonsterData/MonsterDataRow.h"


UC_RandomMove::UC_RandomMove()
{
	NodeName = "Task_RandomVecterMove";
	bNotifyTick = true;
}

EBTNodeResult::Type UC_RandomMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	if (!IsValid(Controller)) {
		UE_LOG(LogTemp, Warning, TEXT("MonsterController is Not Work BTTESK %d  %s"), __LINE__, ANSI_TO_TCHAR(__FUNCTION__));
		return EBTNodeResult::Failed;
	}
	if (true == IsPerceptionUpdated(Controller)) {
		return EBTNodeResult::Type::Succeeded;
	}
	UMonsterDataObject* Data = Controller->GetMCP()->GetData();
	if (true == Data->PathIsEmpty()) {
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Type::InProgress;
}

void UC_RandomMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	if (Controller->IsValidLowLevel() == false) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	UBlackboardComponent* BlackBoard = GetBlackBoard(&OwnerComp);
	if (false == BlackBoard->IsValidLowLevel()) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	UMonsterDataObject* Data = Controller->GetMCP()->GetData();
	if (true == IsPerceptionUpdated(Controller)) {
		Data->RemovePath();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	//FVector SelfVec = GetSelfLocationNoneZ(&OwnerComp);
	//FVector RanVec = GetBlackBoard(&OwnerComp)->GetValueAsVector(*RandomVector);

	//if (true == Data->PathIsEmpty()) {
	//	if (false == SetPath(SelfVec, RanVec, Data, BlackBoard)) {
	//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//		return;
	//	}
	//}
	if (true == NaviMove(Data, BlackBoard, Controller, OwnerComp)) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
}

bool UC_RandomMove::SetPath(FVector _MyLocation, FVector _TargetLocation, UMonsterDataObject* _Data, UBlackboardComponent* _BBC)
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


bool UC_RandomMove::NaviMove(UMonsterDataObject* _Data, UBlackboardComponent* _BBC, AAIController* _Controller, UBehaviorTreeComponent& OwnerComp)
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (false == NavSystem->IsValidLowLevel()) {
		return true;
	}
	if (true == _Data->PathIsEmpty()) {
		return true;
	}
	FVector TargetNavLocation = _Data->NextPath();
	FVector BottomLocation = GetSelfLocation(&OwnerComp);
	FVector Direction = (TargetNavLocation - BottomLocation);
	AC_MonsterAIBase* Controller = Cast<AC_MonsterAIBase>(_Controller);
	TargetNavLocation.Z = 0;
	BottomLocation.Z = 0;
	float Distance = FVector::Dist(TargetNavLocation, BottomLocation);

#ifdef WITH_EDITOR
	for (const FVector& Location : _Data->GetPath())
	{
		DrawDebugSphere(GetWorld(), Location, 10.0f, 8, FColor::Red, false, 1.0f);
	}
#endif
	

	Controller->GetMCP()->Move(Direction);
	if (Distance <= 100.f) {
		_Data->PathHeadRemove();
		if (false == _Data->PathIsEmpty()) {
			return false;
		}
		else {
			return true;
		}
	}
	return false;
}