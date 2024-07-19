// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_TaskMonsterChase.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "Monster/MonsterData/MonsterDataRow.h"
#include <NavigationSystem.h>
#include "NavigationPath.h"
#include "Player/MainPlayer/C_NickMainPlayer.h"

UC_TaskMonsterChase::UC_TaskMonsterChase()
{
	NodeName = "MonsterChase";
	bNotifyTick = true;
}

bool UC_TaskMonsterChase::SetPath(FVector _MyLocation, FVector _TargetLocation, UMonsterDataObject* _Data, UBlackboardComponent* _BBC)
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem)
	{
		UNavigationPath* NavPath = NavSystem->FindPathToLocationSynchronously(GetWorld(), _MyLocation, _TargetLocation);

		if (NavPath && NavPath->IsValid())
		{
#ifdef WITH_EDITOR
			for (auto& Point : NavPath->GetPath()->GetPathPoints())
			{
				DrawDebugSphere(GetWorld(), Point.Location, 10.0f, 8, FColor::Red, false, 1.0f);
			}
#endif
			_Data->SetPath(NavPath->PathPoints);
			//_BBC->SetValueAsVector(*StartLocation, NavPath->PathPoints[0]);
			_Data->PathHeadRemove();  //이걸 삭제하는 이유는 맨 첫번째 위치는 selflocation의 위치 즉 처음 시작 위치이다.
			return true;


		}
		return false;
	}
	return false;
}

bool UC_TaskMonsterChase::NaviMove(UMonsterDataObject* _Data, UBlackboardComponent* _BBC, AAIController* _Controller, UBehaviorTreeComponent& OwnerComp, float _TargetDistance)
{
	//FVector MyStartLocation = _BBC->GetValueAsVector(*StartLocation);
	FVector TargetNavLocation = _Data->NextPath();
	FVector BottomLocation = GetSelfLocation(&OwnerComp);
	FVector Direction = (TargetNavLocation - BottomLocation);
	AC_MonsterAIBase* Controller = Cast<AC_MonsterAIBase>(_Controller);
	TargetNavLocation.Z = 0;
	BottomLocation.Z = 0;
	float Distance = FVector::Dist(TargetNavLocation, BottomLocation);
	//float RTime = _BBC->GetValueAsFloat(*RunTime);

#ifdef WITH_EDITOR
	for (const FVector& Location : _Data->GetPath())
	{
		DrawDebugSphere(GetWorld(), Location, 10.0f, 8, FColor::Red, false, 1.0f);
	}
#endif


	if (true == MonsterAttack(_Data, _Controller, _TargetDistance)) {		//사거리 계산 하면서 공격은 해야함, 그리고 너무 가까우면 당연히 안가도 됨
		return false;		// return하는 경우는 너무 가까워서
	}

	Controller->GetMCP()->Run(Direction);
	if (Distance <= 100.f) {
		_Data->PathHeadRemove();
		return true;
	}
	return false;
	//bool NeviCheck = _BBC->GetValueAsBool(*NextNavi);
	//if (NeviCheck == NextNaviPath && Navi_Minimum >= Distance)
	//{
	//	_BBC->SetValueAsBool(*NextNavi, PrevNaviPath);
	//	return false;
	//}
	//if (NeviCheck == PrevNaviPath) {
	//	
	//	_BBC->SetValueAsFloat(*RunTime, RTime + _DeltaTime);
	//}
	//else if (NeviCheck == PrevNaviPath && Navi_Minimum <= Distance) {
	//	_BBC->SetValueAsBool(*NextNavi, NextNaviPath);
	//	_BBC->SetValueAsVector(*StartLocation, BottomLocation);

	//	return true;
	//}
	//return false;
}

bool UC_TaskMonsterChase::MonsterAttack(UMonsterDataObject* _Data, AAIController* _Controller, float _Distance)
{
	AC_MonsterAIBase* Controller = Cast<AC_MonsterAIBase>(_Controller);
	UC_MonsterComponent* MCP = Controller->GetMCP();
	if (_Distance <= MCP->GetData()->GetMonsterRange()) {
		if (_Distance >= Minimum_Distance) {
			MCP->RunAttack();
			return false;
		}
		else {
			MCP->Attack();
			return true;
		}
	}
	return false;
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
	UBlackboardComponent* BBC = Controller->GetBlackboardComponent();
	AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));
	AC_NickMainPlayer* Player = Cast<AC_NickMainPlayer>(Target);
	UMonsterDataObject* MonsterData = MCP->GetData();
	FVector SelfLocation = GetSelfLocation(&OwnerComp);
	FVector TargetLocation = Player->GetComponentLocation();
	//FVector MyStartLocation = BBC->GetValueAsVector(*StartLocation);
	float Distance = FVector::Dist(TargetLocation, SelfLocation);

	if (true == Player->GetIsPlayerDieCpp()) {
		Controller->IsFindOff();
		return;
	}

	if (Target->IsValidLowLevel() == false) {
		UE_LOG(LogTemp, Fatal, TEXT("MonsterController is Not Work BTTESK %d  %s"), __LINE__, ANSI_TO_TCHAR(__FUNCTION__));
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (true == MonsterRangeTask(OwnerComp, DeltaSeconds)) {
		return;
	}

	if (Distance <= 800) {
		MonsterData->RemovePath();
		if (true == MonsterAttack(MonsterData, Controller, Distance)) {
			return;
		}
		if (true == MCP->JumpCheck()) {
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return;
		}
		MCP->Run(TargetLocation - SelfLocation);
		return;
	}

	if (true == MonsterData->PathIsEmpty()) {
		if (false == SetPath(SelfLocation, TargetLocation, MonsterData, BBC)) {
			if (true == MCP->JumpCheck()) {		//못가는 경로네
				MonsterData->RemovePath();
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return;
			}
			if (true == MCP->BreakCheck()) {
				MonsterData->RemovePath();
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return;
			}
			MCP->Run(TargetLocation - SelfLocation);
		}
		return;
	}
	else {
		NaviMove(MonsterData, BBC, Controller, OwnerComp, Distance);
		return;
	}
	//*******************************************//
//	if (true == MonsterRangeTask(OwnerComp, DeltaSeconds)) {
//		return;
//	}
//
//
//	FVector TargetLocation = Target->GetActorLocation();
//	FVector SelfLocation = GetSelfLocation(&OwnerComp);
//	float Vec = FVector::Dist(SelfLocation, TargetLocation);
//
//	if (false == MonsterData->PathIsEmpty()) // 만약 경로가 남아있다면? 이동해야한다.
//	{
//		FVector TargetNavLocation = MonsterData->NextPath();
//		SelfLocation.Z = 0;
//		FVector CheckDir = (TargetNavLocation - SelfLocation);
//		Controller->GetMCP()->Run(CheckDir);
//		//if (Vec <= 500.f) {
//		//	MCP->Run(TargetLocation - SelfLocation);		//taskmonsterchase 78줄 하다 정지
//		//	MonsterData->RemovePath();
//		//	if (MCP->JumpCheck() == true) {
//		//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//		//		return;
//		//	}
//		//	return;
//		//}
//		bool NeviCheck = Controller->GetBlackboardComponent()->GetValueAsBool(*NextNavi);
//		if (NeviCheck == NextNaviPath && Navi_Minimum >= CheckDir.Size())
//		{
//			Controller->GetBlackboardComponent()->SetValueAsBool(*NextNavi, PrevNaviPath);
//			return;
//		}
//		else if (NeviCheck == PrevNaviPath && Navi_Minimum <= CheckDir.Size()) {
//			Controller->GetBlackboardComponent()->SetValueAsBool(*NextNavi, NextNaviPath);
//			MonsterData->PathHeadRemove();
//			return;
//		}
//	}
//
//	if (Vec <= 800.f) {
//		MCP->Run(TargetLocation - SelfLocation);		//taskmonsterchase 78줄 하다 정지
//		if (MCP->JumpCheck() == true) {
//			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//			return;
//		}
//		if (MCP->BreakCheck() == true) {
//			UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
//			UNavigationPath* NavPath = NavSystem->FindPathToLocationSynchronously(
//				GetWorld(),
//				SelfLocation,
//				TargetLocation
//			);				//부셔야겠다 라고 했는데, 만약에 갈 수 있으면 부수는 것 만큼 멍청한 짓이 없다.	
//			if (NavPath->GetPathCost() < FLT_MAX) {		//그래서 경로를 일단 찾고   그 경로가 비어있다면? 부수는 로직으로 갈 것
//				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//				return;
//			}
//
//			else {		//갈 수 있는 곳이네? 그러면 경로대로 이동해 그런데 그 경로대로 이동하는 로직은 위에 있기 때문에, 일단 return시킴
//				MonsterData->SetPath(NavPath->PathPoints);
//				MonsterData->PathHeadRemove();  //이걸 삭제하는 이유는 맨 첫번째 위치는 selflocation의 위치 즉 처음 시작 위치이다.
//				return;
//			}
//		}
//	}
//
//	if (Vec <= 1500.f) {
//		//if(Vec > 10000.f){
//		MCP->Run(Target->GetActorLocation() - SelfLocation);
//		return;
//	}
//	else if (Vec <= 3000) {
//		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
//		if (!NavSystem) {
//			return;
//		}
//
//		UNavigationPath* NavPath = NavSystem->FindPathToLocationSynchronously(
//			GetWorld(),
//			SelfLocation,
//			TargetLocation
//		);
//
//#if WITH_EDITOR
//		if (0 == NavPath->PathPoints.Num()) {
//			int a = 0;
//		}
//#endif
//
//		if (NavPath->GetPathCost() < FLT_MAX) {
//			MonsterData->RemovePath();
//			UObject* Object = Controller->GetBlackboardComponent()->GetValueAsObject(*TargetActor);
//			AC_NickMainPlayer* Player = Cast<AC_NickMainPlayer>(Object);
//			FVector TargetLocation_p = Player->GetComponentLocation();
//			if (SelfLocation.Z > TargetLocation_p.Z + 10.f) {
//				MCP->Run(TargetLocation_p - SelfLocation);
//				return;
//			}
//			if (MCP->BreakCheck() == true) {
//				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//				return;
//			}
//		}
//
//		if (true == MonsterData->PathIsEmpty())		//path 즉 경로가 비어있으면 일단 경로 찾아서 넣기
//		{
//			MonsterData->SetPath(NavPath->PathPoints);
//			MonsterData->PathHeadRemove();  //이걸 삭제하는 이유는 맨 첫번째 위치는 selflocation의 위치 즉 처음 시작 위치이다.
//
//
//#if WITH_EDITOR
//			//Path->EnableDebugDrawing(true);
//#endif
//		}
//		if (false == MonsterData->PathIsEmpty()) // 만약 경로가 남아있지 않다면? 이동해야한다.
//		{
//			FVector TargetNavLocation = MonsterData->NextPath();
//			SelfLocation.Z = 0;
//			FVector CheckDir = (TargetNavLocation - SelfLocation);
//			Controller->GetMCP()->Run(CheckDir);
//			bool NeviCheck = Controller->GetBlackboardComponent()->GetValueAsBool(*NextNavi);
//			if (NeviCheck == NextNaviPath && Navi_Minimum >= CheckDir.Size())
//			{
//				Controller->GetBlackboardComponent()->SetValueAsBool(*NextNavi, PrevNaviPath);
//				return;
//			}
//			else if (NeviCheck == PrevNaviPath && Navi_Minimum <= CheckDir.Size()) {
//				Controller->GetBlackboardComponent()->SetValueAsBool(*NextNavi, NextNaviPath);
//				MonsterData->PathHeadRemove();
//				return;
//			}
//		}
//	}
//
//	else {
//		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
//		if (!NavSystem) {
//			return;
//		}
//
//		UNavigationPath* NavPath = NavSystem->FindPathToLocationSynchronously(
//			GetWorld(),
//			SelfLocation,
//			TargetLocation
//		);
//
//#if WITH_EDITOR
//		if (0 == NavPath->PathPoints.Num()) {
//			int a = 0;
//		}
//#endif
//
//		if (true == MonsterData->PathIsEmpty())		//path 즉 경로가 비어있으면 일단 경로 찾아서 넣기
//		{
//			//UNavigationPath* Path = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), SelfLocation, TargetLocation, GetSelf(&OwnerComp));
//			MonsterData->SetPath(NavPath->PathPoints);
//			MonsterData->PathHeadRemove();  //이걸 삭제하는 이유는 맨 첫번째 위치는 selflocation의 위치 즉 처음 시작 위치이다.
//		}
//		if (false == MonsterData->PathIsEmpty()) // 만약 경로가 남아있다면? 이동해야한다.
//		{
//			FVector TargetNavLocation = MonsterData->NextPath();
//			SelfLocation.Z = 0;
//			FVector CheckDir = (TargetNavLocation - SelfLocation);
//			Controller->GetMCP()->Run(CheckDir);
//			bool NeviCheck = Controller->GetBlackboardComponent()->GetValueAsBool(*NextNavi);
//			if (NeviCheck == NextNaviPath && Navi_Minimum >= CheckDir.Size())
//			{
//				Controller->GetBlackboardComponent()->SetValueAsBool(*NextNavi, PrevNaviPath);
//				return;
//			}
//			else if (NeviCheck == PrevNaviPath && Navi_Minimum <= CheckDir.Size()) {
//				Controller->GetBlackboardComponent()->SetValueAsBool(*NextNavi, NextNaviPath);
//				MonsterData->PathHeadRemove();
//				return;
//			}
//			return;
//		}
//	}
//#ifdef WITH_EDITOR
//	UE_LOG(LogTemp, Warning, TEXT("MonsterrChase Task"));
//	UE_LOG(LogTemp, Warning, TEXT("TargetLocation: X = %f  : Y = %f "), TargetLocation.X, TargetLocation.Y);
//	UE_LOG(LogTemp, Warning, TEXT("SelfLocation: X = %f  : Y = %f "), SelfLocation.X, SelfLocation.Y);
//	UE_LOG(LogTemp, Warning, TEXT("Vec: %f"), Vec);
//#endif
//
//
//	return;
//	/*------------------------------------------------------------------------------------------*/

}

bool UC_TaskMonsterChase::MonsterRangeTask(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
{
	//AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	//UC_MonsterComponent* MCP = Controller->GetMCP();
	//UMonsterDataObject* MonsterData = MCP->GetData();

	//AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));
	//if (Target->IsValidLowLevel() == false) {
	//	UE_LOG(LogTemp, Fatal, TEXT("MonsterController is Not Work BTTESK %d  %s"), __LINE__, ANSI_TO_TCHAR(__FUNCTION__));
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	//	return true;
	//}

	//FVector TargetLocation = Target->GetActorLocation();
	//FVector SelfLocation = GetSelfLocation(&OwnerComp);
	//float Vec = FVector::Dist(SelfLocation, TargetLocation);

	//if (Vec <= MCP->GetData()->GetMonsterRange()) {
	//	MonsterData->RemovePath();
	//	if (Vec >= Minimum_Distance) {
	//		MCP->Run(TargetLocation - SelfLocation);
	//		Controller->MoveToActor(Target);			//이게 ai move to이고, 엄청 가까울 때만 작동하게 해서 최대한 줄여봤음
	//		GetController(&OwnerComp)->GetMCP()->RunAttack();
	//		return true;
	//	}
	//	else {
	//		GetController(&OwnerComp)->GetMCP()->Attack();
	//		return true;
	//	}
	//	//if (10.f > GetSelfVelocity(&OwnerComp).Size()) {
	//	//	return;
	//	//}
	//	//else {
	//	//	GetController(&OwnerComp)->GetMCP()->RunAttack();
	//	//	return;
	//	//}
	//}
	//else {
	//	return false;
	//}
	return false;
}



