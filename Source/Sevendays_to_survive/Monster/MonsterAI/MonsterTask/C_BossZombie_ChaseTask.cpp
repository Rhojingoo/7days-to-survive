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

    AC_MonsterAIBase* Controller = GetController(&OwnerComp);
    AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));
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

    EBossZombieChaseTaskState TaskState = static_cast<EBossZombieChaseTaskState>(GetBlackBoard(&OwnerComp)->GetValueAsInt(TEXT("TaskState")));

    if (true == GetBlackBoard(&OwnerComp)->GetValueAsBool(TEXT("IsFirstTick")))
    {
        switch (TaskState)
        {
        case EBossZombieChaseTaskState::Run:
            OnRunStart(OwnerComp);
            break;
        case EBossZombieChaseTaskState::Rush:
            OnRushStart(OwnerComp);
            break;
        case EBossZombieChaseTaskState::RushWait:
            OnRushWaitStart(OwnerComp);
            break;
        default:
            break;
        }
    }
    else
    {
        switch (TaskState)
        {
        case EBossZombieChaseTaskState::Run:
            OnRunTick(OwnerComp, DeltaSeconds);
            break;
        case EBossZombieChaseTaskState::Rush:
            OnRushTick(OwnerComp, DeltaSeconds);
            break;
        case EBossZombieChaseTaskState::RushWait:
            OnRushWaitTick(OwnerComp, DeltaSeconds);
            break;
        default:
            break;
        }
    }

}

void UC_BossZombie_ChaseTask::OnRunStart(UBehaviorTreeComponent& OwnerComp)
{
    AC_BossZombie* BossZombie = Cast<AC_BossZombie>(GetSelf(&OwnerComp));
    AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));

    FVector BossZombieLocation2D = BossZombie->GetActorLocation();
    BossZombieLocation2D.Z = 0;

    FVector TargetLocation2D = Target->GetActorLocation();
    TargetLocation2D.Z = 0;

    BossZombie->Run(TargetLocation2D - BossZombieLocation2D);
    BossZombie->ApplyRunSpeed();

    GetBlackBoard(&OwnerComp)->SetValueAsBool(TEXT("IsFirstTick"), false);

    FTimerHandle UnusedHandle;
    FTimerDelegate Delegate;
    Delegate.BindUObject(this, &UC_BossZombie_ChaseTask::OnRunEnd, &OwnerComp);
    BossZombie->GetWorldTimerManager().SetTimer(UnusedHandle, Delegate, RunTime, false);
}

void UC_BossZombie_ChaseTask::OnRunTick(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
{
    AC_BossZombie* BossZombie = Cast<AC_BossZombie>(GetSelf(&OwnerComp));
    AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));

    FVector BossZombieLocation2D = BossZombie->GetActorLocation();
    BossZombieLocation2D.Z = 0;

    FVector TargetLocation2D = Target->GetActorLocation();
    TargetLocation2D.Z = 0;

    BossZombie->AddMovementInput(TargetLocation2D - BossZombieLocation2D);
}

void UC_BossZombie_ChaseTask::OnRunEnd(UBehaviorTreeComponent* OwnerComp)
{
    GetBlackBoard(OwnerComp)->SetValueAsInt(TEXT("TaskState"), static_cast<int>(EBossZombieChaseTaskState::Rush));
    GetBlackBoard(OwnerComp)->SetValueAsBool(TEXT("IsFirstTick"), true);
}

void UC_BossZombie_ChaseTask::OnRushStart(UBehaviorTreeComponent& OwnerComp)
{
    AC_BossZombie* BossZombie = Cast<AC_BossZombie>(GetSelf(&OwnerComp));
    AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));

    FVector BossZombieLocation2D = BossZombie->GetActorLocation();
    BossZombieLocation2D.Z = 0;

    FVector RushTargetLocation2D = Target->GetActorLocation();
    RushTargetLocation2D.Z = 0;

    GetBlackBoard(&OwnerComp)->SetValueAsVector(TEXT("RushDirection"), RushTargetLocation2D - BossZombieLocation2D);

    BossZombie->Rush();
    BossZombie->ApplyRushSpeed();
    BossZombie->AttackCollisionOn();

    GetBlackBoard(&OwnerComp)->SetValueAsBool(TEXT("IsFirstTick"), false);

    FTimerHandle UnusedHandle;
    FTimerDelegate Delegate;
    Delegate.BindUObject(this, &UC_BossZombie_ChaseTask::OnRushEnd, &OwnerComp);
    BossZombie->GetWorldTimerManager().SetTimer(UnusedHandle, Delegate, RushTime, false);
}

void UC_BossZombie_ChaseTask::OnRushTick(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
{
    AC_BossZombie* BossZombie = Cast<AC_BossZombie>(GetSelf(&OwnerComp));
    FVector RushDirection = GetBlackBoard(&OwnerComp)->GetValueAsVector(TEXT("RushDirection"));

    BossZombie->AddMovementInput(RushDirection);
}

void UC_BossZombie_ChaseTask::OnRushEnd(UBehaviorTreeComponent* OwnerComp)
{
    AC_BossZombie* BossZombie = Cast<AC_BossZombie>(GetSelf(OwnerComp));
    GetBlackBoard(OwnerComp)->SetValueAsInt(TEXT("TaskState"), static_cast<int>(EBossZombieChaseTaskState::RushWait));
    GetBlackBoard(OwnerComp)->SetValueAsBool(TEXT("IsFirstTick"), true);
    BossZombie->AttackCollisionOff();
}

void UC_BossZombie_ChaseTask::OnRushWaitStart(UBehaviorTreeComponent& OwnerComp)
{
    AC_BossZombie* BossZombie = Cast<AC_BossZombie>(GetSelf(&OwnerComp));
    BossZombie->RushWait();

    GetBlackBoard(&OwnerComp)->SetValueAsBool(TEXT("IsFirstTick"), false);

    FTimerHandle UnusedHandle;
    FTimerDelegate Delegate;
    Delegate.BindUObject(this, &UC_BossZombie_ChaseTask::OnRushWaitEnd, &OwnerComp);
    BossZombie->GetWorldTimerManager().SetTimer(UnusedHandle, Delegate, RushWaitTime, false);
}

void UC_BossZombie_ChaseTask::OnRushWaitTick(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
{
}

void UC_BossZombie_ChaseTask::OnRushWaitEnd(UBehaviorTreeComponent* OwnerComp)
{
    GetBlackBoard(OwnerComp)->SetValueAsInt(TEXT("TaskState"), static_cast<int>(EBossZombieChaseTaskState::Run));
    GetBlackBoard(OwnerComp)->SetValueAsBool(TEXT("IsFirstTick"), true);
}
