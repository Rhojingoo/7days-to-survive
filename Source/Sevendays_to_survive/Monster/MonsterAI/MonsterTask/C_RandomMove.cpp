// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_RandomMove.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"

UC_RandomMove::UC_RandomMove()
{
	NodeName = "Task_RandomVecterMove";
	bNotifyTick = true;
}

EBTNodeResult::Type UC_RandomMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	if (true == IsPerceptionUpdated(Controller)) {
		return EBTNodeResult::Type::Succeeded;
	}
	return EBTNodeResult::Type::InProgress;
}

void UC_RandomMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);



	AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	UBlackboardComponent* BlackBoard = GetBlackBoard(&OwnerComp);
	if (true == IsPerceptionUpdated(Controller)) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	
	UAIPerceptionComponent* APC = Controller->GetAPC();
	APC->SaveConfig();
	UAISenseConfig_Hearing* HearingConfig = Controller->GetHearingConfig();
	//for (AActor* Actor : UpdatedActors)
	//{
	//	// 소리를 감지한 액터에 대해 처리할 로직 작성
	//	UE_LOG(LogTemp, Warning, TEXT("Heard actor: %s"), *Actor->GetName());
	//}

	FVector SelfVec = GetSelfLocationNoneZ(&OwnerComp);
	FVector RanVec = GetBlackBoard(&OwnerComp)->GetValueAsVector(*RandomVector);
	FVector Direction = (RanVec - SelfVec).GetSafeNormal();


	GetController(&OwnerComp)->GetMCP()->Move(Direction);

	float Vec = FVector::Dist(SelfVec, RanVec);

#ifdef WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("RandomMove Task"));
	UE_LOG(LogTemp, Warning, TEXT("Self: %f"), SelfVec);
	UE_LOG(LogTemp, Warning, TEXT("Ran: %f"), RanVec);
	UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Vec);
#endif

	if (Vec < 100.f) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
