// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_BossZombie_ChaseTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "Monster/MonsterData/MonsterDataRow.h"
#include "Monster/C_BossZombie.h"
#include "TimerManager.h"

UC_BossZombie_ChaseTask::UC_BossZombie_ChaseTask()
{
    NodeName = "BossZombieChase";
    bNotifyTick = true;
}

EBTNodeResult::Type UC_BossZombie_ChaseTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    BossZombie = Cast<AC_BossZombie>(GetSelf(&OwnerComp));
    AC_MonsterAIBase* Controller = GetController(&OwnerComp);
    Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));
    if (Target->IsValidLowLevel() == false) {
        return EBTNodeResult::Failed;
    }
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

    if (true == IsFirstTick)
    {
        switch (TaskState)
        {
        case UC_BossZombie_ChaseTask::ETaskState::Run:
            OnRunStart();
            break;
        case UC_BossZombie_ChaseTask::ETaskState::Rush:
            OnRushStart();
            break;
        case UC_BossZombie_ChaseTask::ETaskState::RushWait:
            OnRushWaitStart();
            break;
        default:
            break;
        }
    }
    else
    {
        switch (TaskState)
        {
        case UC_BossZombie_ChaseTask::ETaskState::Run:
            OnRunTick(DeltaSeconds);
            break;
        case UC_BossZombie_ChaseTask::ETaskState::Rush:
            OnRushTick(DeltaSeconds);
            break;
        case UC_BossZombie_ChaseTask::ETaskState::RushWait:
            OnRushWaitTick(DeltaSeconds);
            break;
        default:
            break;
        }
    }

}

void UC_BossZombie_ChaseTask::OnRunStart()
{
    FVector BossZombieLocation2D = BossZombie->GetActorLocation();
    BossZombieLocation2D.Z = 0;

    FVector TargetLocation2D = Target->GetActorLocation();
    TargetLocation2D.Z = 0;

    BossZombie->Run(TargetLocation2D - BossZombieLocation2D);
    BossZombie->ApplyRunSpeed();

    IsFirstTick = false;

    FTimerHandle UnusedHandle;
    BossZombie->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UC_BossZombie_ChaseTask::OnRunEnd, RunTime, false);
}

void UC_BossZombie_ChaseTask::OnRunTick(float DeltaSeconds)
{
    FVector BossZombieLocation2D = BossZombie->GetActorLocation();
    BossZombieLocation2D.Z = 0;

    FVector TargetLocation2D = Target->GetActorLocation();
    TargetLocation2D.Z = 0;

    BossZombie->AddMovementInput(TargetLocation2D - BossZombieLocation2D);
}

void UC_BossZombie_ChaseTask::OnRunEnd()
{
    TaskState = ETaskState::Rush;
    IsFirstTick = true;
}

void UC_BossZombie_ChaseTask::OnRushStart()
{
    FVector BossZombieLocation2D = BossZombie->GetActorLocation();
    BossZombieLocation2D.Z = 0;

    FVector RushTargetLocation2D = Target->GetActorLocation();
    RushTargetLocation2D.Z = 0;

    RushDirection = RushTargetLocation2D - BossZombieLocation2D;

    BossZombie->Rush();
    BossZombie->ApplyRushSpeed();
    BossZombie->AttackCollisionOn();

    IsFirstTick = false;

    FTimerHandle UnusedHandle;
    BossZombie->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UC_BossZombie_ChaseTask::OnRushEnd, RushTime, false);
}

void UC_BossZombie_ChaseTask::OnRushTick(float DeltaSeconds)
{
    BossZombie->AddMovementInput(RushDirection);
}

void UC_BossZombie_ChaseTask::OnRushEnd()
{
    TaskState = ETaskState::RushWait;
    IsFirstTick = true;
    BossZombie->AttackCollisionOff();
}

void UC_BossZombie_ChaseTask::OnRushWaitStart()
{
    BossZombie->RushWait();

    IsFirstTick = false;

    FTimerHandle UnusedHandle;
    BossZombie->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UC_BossZombie_ChaseTask::OnRushWaitEnd, RushWaitTime, false);
}

void UC_BossZombie_ChaseTask::OnRushWaitTick(float DeltaSeconds)
{
}

void UC_BossZombie_ChaseTask::OnRushWaitEnd()
{
    TaskState = ETaskState::Run;
    IsFirstTick = true;
}
