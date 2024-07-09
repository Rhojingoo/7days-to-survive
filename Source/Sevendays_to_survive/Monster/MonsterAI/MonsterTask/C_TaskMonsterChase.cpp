// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_TaskMonsterChase.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "Monster/MonsterData/MonsterDataRow.h"
#include <NavigationSystem.h>
#include "NavigationPath.h"

UC_TaskMonsterChase::UC_TaskMonsterChase()
{
	NodeName = "MonsterChase";
	bNotifyTick = true;
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
		return EBTNodeResult::InProgress;
	}

	else {
		return EBTNodeResult::Failed;
	}
}

void UC_TaskMonsterChase::InitTask(UBehaviorTreeComponent* OwnerComp)
{
	Super::InitTask(OwnerComp);
}

void UC_TaskMonsterChase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	UC_MonsterComponent* MCP = Controller->GetMCP();
	AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));
	if (Target->IsValidLowLevel() == false) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}


	FVector TargetLocation = Target->GetActorLocation();
	TargetLocation.Z = 0;
	FVector SelfLocation = GetSelfLocationNoneZ(&OwnerComp);
	float Vec = FVector::Dist(SelfLocation, TargetLocation);

	if (Vec >= 1500.f) {
		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if (!NavSystem) {
			return;
		}

		UNavigationPath* NavPath = NavSystem->FindPathToLocationSynchronously(
			GetWorld(),
			SelfLocation,
			TargetLocation
		);

		UMonsterDataObject* MonsterData = Controller->GetMCP()->GetData();

		if (NavPath->GetPathCost() < FLT_MAX) {
			int a = 0;
		}

		if (true == MonsterData->PathIsEmpty())		//path 즉 경로가 비어있으면 일단 경로 찾아서 넣기
		{
			//UNavigationPath* Path = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), SelfLocation, TargetLocation, GetSelf(&OwnerComp));
			MonsterData->SetPath(NavPath->PathPoints);
			if (MonsterData->GetPathLength() > 3) {
				int a = 0;
			}
			MonsterData->PathHeadRemove();  //이걸 삭제하는 이유는 맨 첫번째 위치는 selflocation의 위치 즉 처음 시작 위치이다.


#if WITH_EDITOR
			//Path->EnableDebugDrawing(true);
#endif
		}
		if (false == MonsterData->PathIsEmpty()) // 만약 경로가 남아있지 않다면? 이동해야한다.
		{
			TargetLocation = MonsterData->NextPath();
			TargetLocation.Z = 0;

			FVector CheckDir = (TargetLocation - SelfLocation);
			Controller->GetMCP()->Run(CheckDir);
			if (10.0f >= CheckDir.Size())
			{
				MonsterData->PathHeadRemove();
			}
			else if (Vec < Minimum_Distance) {
				GetController(&OwnerComp)->GetMCP()->Attack();
				return;
				//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}

			else if (Vec < MCP->GetData()->GetMonsterRange()) {
				GetController(&OwnerComp)->GetMCP()->RunAttack();
				return;
			}
		}
		else {
			return;
		}
	}
	else {
		MCP->Run(Target->GetActorLocation() - SelfLocation);
		if (Vec < Minimum_Distance) {
			GetController(&OwnerComp)->GetMCP()->Attack();
			return;
			//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}

		else if (Vec < MCP->GetData()->GetMonsterRange()) {
			GetController(&OwnerComp)->GetMCP()->RunAttack();
			return;
		}
		return;
	}



#ifdef WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("MonsterrChase Task"));
	UE_LOG(LogTemp, Warning, TEXT("TargetLocation: X = %f  : Y = %f "), TargetLocation.X, TargetLocation.Y);
	UE_LOG(LogTemp, Warning, TEXT("SelfLocation: X = %f  : Y = %f "), SelfLocation.X, SelfLocation.Y);
	UE_LOG(LogTemp, Warning, TEXT("Vec: %f"), Vec);
#endif


	return;
	/*------------------------------------------------------------------------------------------*/

}



