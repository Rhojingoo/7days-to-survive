// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_BreakTimeTask.h"
#include <NavigationSystem.h>
#include "NavigationPath.h"

UC_BreakTimeTask::UC_BreakTimeTask()
{
	bNotifyTick = true;
	NodeName = "BreakTimeTask";
}

EBTNodeResult::Type UC_BreakTimeTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AC_MonsterAIBase* Controller =  GetController(&OwnerComp);
	if (false == Controller->IsValidLowLevel()) {
		return EBTNodeResult::Failed;
	}
	if (true == Controller->GetMCP()->BreakCheck()) {
		return EBTNodeResult::InProgress;
	}
	else {
		return EBTNodeResult::Failed;
	}
}

void UC_BreakTimeTask::InitTask(UBehaviorTreeComponent* OwnerComp)
{
	Super::InitTask(OwnerComp);
}

void UC_BreakTimeTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	if (false == Controller->IsValidLowLevel()) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
		return;
	}
	UBlackboardComponent* BBC = Controller->GetBlackboardComponent();
	if (false == BBC->IsValidLowLevel()) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
		return;
	}
	if (false == GetController(&OwnerComp)->GetMCP()->BreakCheck()) {  // 벽이 있니? 없으면
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);		// 이미 벽이 부서진것이니 그만 때려
		return;
	}
	Controller->GetMCP()->Attack();		//  벽이 아직 있구나? 때려라
	float FBreakTime = BBC->GetValueAsFloat(*BreakTime);  //지금 몇 초나 때렸니?
	if (FBreakTime < Minimum_BreakTime) {		//5초 이하면 더 때리고
		BBC->SetValueAsFloat(*BreakTime, FBreakTime + DeltaSeconds);
		return;
	}
	else {
		BBC->SetValueAsFloat(*BreakTime, FBreakTime + DeltaSeconds); //5초 이상 때렸으니, 확인좀 해보자
		UC_MonsterComponent* MCP = Controller->GetMCP();
		AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));
		if (Target->IsValidLowLevel() == false) {
			UE_LOG(LogTemp, Fatal, TEXT("절대로 접근할 수 없는 노드"));
			return;
		}

		FVector TargetLocation = Target->GetActorLocation();
		FVector SelfLocation = GetSelfLocation(&OwnerComp);
		float Vec = FVector::Dist(SelfLocation, TargetLocation);



		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if (!NavSystem) {
			return;
		}

		UNavigationPath* NavPath = NavSystem->FindPathToLocationSynchronously(
			GetWorld(),
			SelfLocation,
			TargetLocation
		);

		if (NavPath->GetPathCost() < FLT_MAX) {		//갈 수 없어?
			if (Vec > Max_Distance) //그러면 3000보다 멀어? max가 3000임
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
				return;
			}
		}
		return;			//갈 수 없는 곳인데, 아직 멀지도 않아? 그러면 계속 벽이나 때려
	}
}