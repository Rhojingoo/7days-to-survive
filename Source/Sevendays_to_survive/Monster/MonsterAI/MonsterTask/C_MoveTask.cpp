// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_MoveTask.h"
#include "Monster/C_ScreamZombie.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"

UC_MoveTask::UC_MoveTask()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UC_MoveTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AC_MonsterAIBase* Controller = GetController(&OwnerComp);
	if (!IsValid(Controller)) {
		UE_LOG(LogTemp, Warning, TEXT("MonsterController is Not Work BTTESK %d  %s"), __LINE__, ANSI_TO_TCHAR(__FUNCTION__));
		return EBTNodeResult::Failed;
	}
	if (true == Controller->GetIsFind()) {
		return EBTNodeResult::Type::Succeeded;
	}
	else if (true == Controller->GetIsSound()) {
		return EBTNodeResult::Type::InProgress;
	}
	else {
		return EBTNodeResult::Type::Failed;
	}

	//애니메이션이 변경이 안되네 전체적으로 소리들을때 무브투로가면 무조건 
}

void UC_MoveTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AC_MonsterAIBase* Controller = GetController(&OwnerComp);

	if (true == Controller->GetIsFind()) 
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	FVector SelfLocation = GetSelfLocation(&OwnerComp);
	SelfLocation.Z = 0;
	FVector TargetLocation = Controller->GetBlackboardComponent()->GetValueAsVector(*SoundVector);
	TargetLocation.Z = 0;
	FVector Dist = TargetLocation - SelfLocation;	

	bool check = Controller->GetBlackboardComponent()->GetValueAsBool(*FollowZombie);
	
	if (Dist.Size() <= AcceptableRadius && Controller->GetBlackboardComponent()->GetValueAsBool(*FollowZombie) == false)
	{
		Controller->GetBlackboardComponent()->SetValueAsBool(*FollowZombie, true);
	}
	else if (Controller->GetBlackboardComponent()->GetValueAsBool(*FollowZombie) == true) // 스크림 좀비를 따라 가는중
	{
		AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*ScreamZombie));
		AC_ScreamZombie* SC_ZOMBIE = Cast<AC_ScreamZombie>(Target);
		if (Target == nullptr)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			Controller->SetIsSound(false);
			return;
		}

		if (SC_ZOMBIE != nullptr)
		{
			if (SC_ZOMBIE->TargetDie == true)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
				Controller->SetIsSound(false);
				return;
			}
		}
		FVector MonLocation = Target->GetActorLocation();
		FVector Distance = MonLocation - SelfLocation;
		Controller->GetMCP()->Run(Distance);
	}
	else // 플레이어를 보고 소리 지른곳으로 가능중
	{
		AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*ScreamZombie));
		AC_ScreamZombie* SC_ZOMBIE = Cast<AC_ScreamZombie>(Target);

		if (Target == nullptr)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			Controller->SetIsSound(false);
			return;
		}

		if (SC_ZOMBIE != nullptr)
		{
			if (SC_ZOMBIE->TargetDie == true)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
				Controller->SetIsSound(false);
				return;
			}
		}
		Controller->GetMCP()->Run(Dist);
	}
}

