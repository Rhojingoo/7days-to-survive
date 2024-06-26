// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_TaskMonsterPatrol.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"

UC_TaskMonsterPatrol::UC_TaskMonsterPatrol()
{
	NodeName = "MonsterPatrol";
	bNotifyTick = true;
}

void UC_TaskMonsterPatrol::InitTask(UBehaviorTreeComponent* OwnerComp)
{
	Super::InitTask(OwnerComp);
}

EBTNodeResult::Type UC_TaskMonsterPatrol::PatrolMove(AC_MonsterAIBase* _MonsterController)
{
	//FVector Origin = FVector(_MonsterController->GetPawn()->GetActorLocation()); // �ڱ� �ڽ��� ��ġ (��: ���� Actor�� ��ġ)
	//float Radius = 1000.0f; // �ݰ�
	//RandomVector = GetRandomVectorInRadius(Origin, Radius);
	//UE_LOG(LogTemp, Log, TEXT("Random Vector in Radius: %s"), *RandomVector.ToString());

	//EPathFollowingRequestResult::Type MoveResult = _MonsterController->MoveToLocation(RandomVector);
	//if (MoveResult == EPathFollowingRequestResult::Failed)
	//{
	//	return EBTNodeResult::Failed;
	//}
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UC_TaskMonsterPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (TaskController->GetIsFind() == true) {
		return EBTNodeResult::Succeeded;
	}

	if (!IsValid(TaskController)) {
		UE_LOG(LogTemp, Warning, TEXT("MonsterController is Not Work BTTESK %d  %s"), __LINE__, ANSI_TO_TCHAR(__FUNCTION__));
		return EBTNodeResult::Failed;
	}

	else {
		BlackboardComp->SetValueAsBool(*BoolName, false);
		return PatrolMove(TaskController);
	}
	//return EBTNodeResult::Failed;
}

void UC_TaskMonsterPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	//if (TaskController->GetIsFind() || TaskController->GetMoveStatus() != EPathFollowingStatus::Moving) {
	//	TaskController->GetBlackboardComponent()->SetValueAsBool(*BoolName, true);
	//	RandomVector = FVector::ZeroVector;
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//	return;
	//}
}

// �־��� �ݰ� ������ ���� ���͸� ��ȯ�ϴ� �Լ�
FVector UC_TaskMonsterPatrol::GetRandomVectorInRadius(const FVector& Origin, float Radius)
{
	// �� ������ ���� ��ġ�� ����
	FVector RandomUnitVector = UKismetMathLibrary::RandomUnitVector();
	float RandomDistance = FMath::FRandRange(0.0f, Radius);

	return Origin + RandomUnitVector * RandomDistance;
}