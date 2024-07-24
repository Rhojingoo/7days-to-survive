// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_Task_MonsterShout.h"
#include "Kismet/GameplayStatics.h"
#include "Monster/C_ScreamZombie.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "Monster/MonsterData/MonsterDataRow.h"

UC_Task_MonsterShout::UC_Task_MonsterShout()
{
	NodeName = "MonsterShout";
	bNotifyTick = true;
}

EBTNodeResult::Type UC_Task_MonsterShout::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

void UC_Task_MonsterShout::InitTask(UBehaviorTreeComponent* OwnerComp)
{
	Super::InitTask(OwnerComp);
}

void UC_Task_MonsterShout::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	UC_MonsterComponent* MCP = Controller->GetMCP();

	AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));
	if (Target->IsValidLowLevel() == false) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	FVector TargetLocation = Target->GetActorLocation();
	TargetLocation.Z = 0;

	FVector SelfLocation = GetSelfLocationNoneZ(&OwnerComp);

	MCP->Shout();
	//AC_ZombieBase* Zombie = MCP->GetMonster();
	AC_ZombieBase* Scream_Zombie = MCP->GetMonster();
	//AC_ScreamZombie* Scream_Zombie = Cast<AC_ScreamZombie>(Zombie);
	//if (Scream_Zombie == nullptr)
	//{
	//	int a = 0;
	//	return;
	//}
	bool ShoutCheck = Scream_Zombie->IsShout();

	FVector Direction = (Target->GetActorLocation() - SelfLocation).GetSafeNormal();

	FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	Controller->GetPawn()->SetActorRotation(LookAtRotation);

	float Vec = FVector::Dist(SelfLocation, TargetLocation);

#ifdef WITH_EDITOR
	//UE_LOG(LogTemp, Warning, TEXT("MonsterrChase Task"));
	//UE_LOG(LogTemp, Warning, TEXT("TargetLocation: X = %f  : Y = %f "), TargetLocation.X, TargetLocation.Y);
	//UE_LOG(LogTemp, Warning, TEXT("SelfLocation: X = %f  : Y = %f "), SelfLocation.X, SelfLocation.Y);
	//UE_LOG(LogTemp, Warning, TEXT("Vec: %f"), Vec);
#endif

	if (ShoutCheck == true)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	return;
}
