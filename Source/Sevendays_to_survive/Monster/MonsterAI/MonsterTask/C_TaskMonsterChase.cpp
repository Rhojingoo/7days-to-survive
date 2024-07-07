// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_TaskMonsterChase.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"

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

	AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));
	if (Target->IsValidLowLevel() == false) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	FVector TargetLocation = Target->GetActorLocation();
	TargetLocation.Z = 0;

	FVector SelfLocation = GetSelfLocationNoneZ(&OwnerComp);

	GetController(&OwnerComp)->GetMCP()->Run(Target->GetActorLocation() - SelfLocation);

	float Vec = FVector::Dist(SelfLocation, TargetLocation);

#ifdef WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("MonsterrChase Task"));
	UE_LOG(LogTemp, Warning, TEXT("TargetLocation: X = %f  : Y = %f "), TargetLocation.X, TargetLocation.Y);
	UE_LOG(LogTemp, Warning, TEXT("SelfLocation: X = %f  : Y = %f "), SelfLocation.X, SelfLocation.Y);
	UE_LOG(LogTemp, Warning, TEXT("Vec: %f"), Vec);
#endif

	if (Vec < TargetDistance) {
		GetController(&OwnerComp)->GetMCP()->Attack();
		return;
		//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	else if (Vec < 200.f) {
		GetController(&OwnerComp)->GetMCP()->RunAttack();
		return;
	}

	return;
}


