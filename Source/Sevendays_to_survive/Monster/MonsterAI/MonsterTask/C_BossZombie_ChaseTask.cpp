// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_BossZombie_ChaseTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "Monster/MonsterData/MonsterDataRow.h"
#include "Monster/C_BossZombie.h"

UC_BossZombie_ChaseTask::UC_BossZombie_ChaseTask()
{
    NodeName = "BossZombieChase";
    bNotifyTick = true;
}

EBTNodeResult::Type UC_BossZombie_ChaseTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

void UC_BossZombie_ChaseTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AC_BossZombie* BossZombie = Cast<AC_BossZombie>(GetSelf(&OwnerComp));
    AC_MonsterAIBase* Controller = GetController(&OwnerComp);
    UC_MonsterComponent* MCP = Controller->GetMCP();
    AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));
    if (Target->IsValidLowLevel() == false) {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    }

    if (true == IsRushWaiting && true == IsFirstTick)
    {
        RushWaitTimer = RushWaitCooldown;

        BossZombie->RushWait();

        IsFirstTick = false;
    }
    else if (true == IsRushWaiting && false == IsFirstTick)
    {
        RushWaitTimer -= DeltaSeconds;
        if (RushWaitTimer <= 0.0f)
        {
            IsRushWaiting = false;
            IsFirstTick = true;
        }
    }
    else if (false == IsRushWaiting && true == IsFirstTick)
    {
        RushTargetHorizontalLocation = Target->GetActorLocation();
        RushTargetHorizontalLocation.Z = 0;

        BossZombie->Rush();

        IsFirstTick = false;
    }
    else if (false == IsRushWaiting && false == IsFirstTick)
    {
        FVector BossZombieHorizontalLocation = BossZombie->GetActorLocation();
        BossZombieHorizontalLocation.Z = 0;

        BossZombie->AddMovementInput(RushTargetHorizontalLocation - BossZombieHorizontalLocation);

        if (FVector::Dist2D(BossZombieHorizontalLocation, RushTargetHorizontalLocation) < 10.0f)
        {
            IsRushWaiting = true;
            IsFirstTick = true;
        }
    }
}
