// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_MoveTask.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"

UC_MoveTask::UC_MoveTask()
{
	//bNotifyTick = true;
}

EBTNodeResult::Type UC_MoveTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	if (true == Controller->GetIsFind()) {
		return EBTNodeResult::Type::Succeeded;
	}
	else if (true == Controller->GetIsSound()) {
		return EBTNodeResult::Type::InProgress;
	}
	else {
		return EBTNodeResult::Type::Failed;
	}
}

void UC_MoveTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AC_MonsterAIBase* Controller = GetController(&OwnerComp);

	if (true == Controller->GetIsFind()) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	FVector SelfLocation = GetSelfLocation(&OwnerComp);
	SelfLocation.Z = 0;
	AActor* Actor = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(*TargetActor));
	FVector TargetLocation = Actor->GetActorLocation();
	FVector Dist = TargetLocation - SelfLocation;
	Controller->GetMCP()->Move(Dist);

	//	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	//	if (!NavSystem) {
	//		return;
	//	}
	//
	//	UNavigationPath* NavPath = NavSystem->FindPathToLocationSynchronously(
	//		GetWorld(),
	//		SelfLocation,
	//		TargetLocation
	//	);
	//
	//	UMonsterDataObject* MonsterData = Controller->GetMCP()->GetData();
	//
	//	if (NavPath->GetPathCost() < FLT_MAX) {
	//		int a = 0;
	//	}
	//
	//	if (true == MonsterData->PathIsEmpty())		//path 즉 경로가 비어있으면 일단 경로 찾아서 넣기
	//	{
	//		//UNavigationPath* Path = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), SelfLocation, TargetLocation, GetSelf(&OwnerComp));
	//		MonsterData->SetPath(NavPath->PathPoints);
	//		if (MonsterData->GetPathLength() > 3) {
	//			int a = 0;
	//		}
	//		MonsterData->PathHeadRemove();  //이걸 삭제하는 이유는 맨 첫번째 위치는 selflocation의 위치 즉 처음 시작 위치이다.
	//
	//
	//#if WITH_EDITOR
	//		//Path->EnableDebugDrawing(true);
	//#endif
	//	}
	//	if (false == MonsterData->PathIsEmpty()) // 만약 경로가 남아있지 않다면? 이동해야한다.
	//	{
	//		TargetLocation = MonsterData->NextPath();
	//		TargetLocation.Z = 0;
	//
	//		FVector CheckDir = (TargetLocation - SelfLocation);
	//		Controller->GetMCP()->Run(CheckDir);
	//		if (10.0f >= CheckDir.Size())
	//		{
	//			MonsterData->PathHeadRemove();
	//		}
	//	}
	//	else {
	//		return;
	//	}

}

