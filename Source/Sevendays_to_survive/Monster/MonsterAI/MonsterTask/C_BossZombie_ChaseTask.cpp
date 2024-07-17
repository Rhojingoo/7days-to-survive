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

bool UC_BossZombie_ChaseTask::MonsterRangeTask(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
{
    EBossZombieChaseTaskState State = GetState(OwnerComp);
    if (State == EBossZombieChaseTaskState::Run)
    {
        return MonsterRangeTaskOnRun(OwnerComp, DeltaSeconds);
    }
    else if (State == EBossZombieChaseTaskState::Rush)
    {
        return MonsterRangeTaskOnRush(OwnerComp, DeltaSeconds);
    }
    else if (State == EBossZombieChaseTaskState::Faint)
    {
        return MonsterRangeTaskOnFaint(OwnerComp, DeltaSeconds);
    }
    return false;
}

bool UC_BossZombie_ChaseTask::MonsterRangeTaskOnRun(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
{
    AC_MonsterAIBase* Controller = GetController(&OwnerComp);
    UC_MonsterComponent* MCP = Controller->GetMCP();
    UMonsterDataObject* MonsterData = MCP->GetData();
    AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));

    FVector TargetLocation = Target->GetActorLocation();
    FVector SelfLocation = GetSelfLocation(&OwnerComp);
    TargetLocation.Z = 0.0f;
    SelfLocation.Z = 0.0f;
    float Vec = FVector::Dist(SelfLocation, TargetLocation);

    AddTimer(OwnerComp, -DeltaSeconds);
    float Timer = GetTimer(OwnerComp);

    // 1. 공격 범위 안에 있으면 일반 공격
    if (Vec <= MCP->GetData()->GetMonsterRange())
    {
        MonsterData->RemovePath();

        if (Vec >= Minimum_Distance) {
            MCP->Run(TargetLocation - SelfLocation);
            Controller->MoveToActor(Target);
            GetController(&OwnerComp)->GetMCP()->RunAttack();
        }
        else {
            GetController(&OwnerComp)->GetMCP()->Attack();
        }

        return true;
    }

    // 2. 막혀 있거나, 너무 멀거나, 돌진 쿨이 돌지 않았으면 돌진하지 않는다.
    if (true == MCP->BreakCheck() || true == MCP->JumpCheck() || Vec > 3000.0f || Timer > 0.0f)
    {
        return false;
    }

    // 4. 그 외의 경우 돌진
    SetState(OwnerComp, EBossZombieChaseTaskState::Rush);

    AC_BossZombie* Boss = Cast<AC_BossZombie>(GetSelf(&OwnerComp));
    Boss->Rush();
    Boss->PlayRushSound();
    Boss->ApplyRushSpeed();
    Boss->AttackCollisionOn();
    SetTimer(OwnerComp, RushTime);
    return true;
}

bool UC_BossZombie_ChaseTask::MonsterRangeTaskOnRush(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
{
    AC_MonsterAIBase* Controller = GetController(&OwnerComp);
    UC_MonsterComponent* MCP = Controller->GetMCP();
    UMonsterDataObject* MonsterData = MCP->GetData();
    AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));

    FVector TargetLocation = Target->GetActorLocation();
    FVector SelfLocation = GetSelfLocation(&OwnerComp);
    TargetLocation.Z = 0.0f;
    SelfLocation.Z = 0.0f;

    AddTimer(OwnerComp, -DeltaSeconds);
    AC_BossZombie* Boss = Cast<AC_BossZombie>(GetSelf(&OwnerComp));
    Boss->AddMovementInput(TargetLocation - SelfLocation);

    // 1. 부딪힌 경우 돌진 중지
    if (true == MCP->BreakCheck() || true == MCP->JumpCheck())
    {
        Boss->Faint();
        Boss->ApplyFaintSpeed();
        SetTimer(OwnerComp, FaintTime);
        SetState(OwnerComp, EBossZombieChaseTaskState::Faint);
        Boss->AttackCollisionOff();
        return true;
    }

    // 2. 돌진 시간이 다 된 경우 돌진 중지
    if (GetTimer(OwnerComp) <= 0.0f)
    {
        Boss->Faint();
        Boss->ApplyFaintSpeed();
        SetTimer(OwnerComp, FaintTime);
        SetState(OwnerComp, EBossZombieChaseTaskState::Faint);
        Boss->AttackCollisionOff();
        return true;
    }

    return true;
}

bool UC_BossZombie_ChaseTask::MonsterRangeTaskOnFaint(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
{
    AddTimer(OwnerComp, -DeltaSeconds);
    AC_BossZombie* Boss = Cast<AC_BossZombie>(GetSelf(&OwnerComp));

    // 기절 시간이 다 된 경우 다시 추격
    if (GetTimer(OwnerComp) <= 0.0f)
    {
        Boss->ApplyRunSpeed();
        SetTimer(OwnerComp, RushCoolDown);
        SetState(OwnerComp, EBossZombieChaseTaskState::Run);
        Boss->MontageStop();
        return true;
    }

    return true;
}

EBossZombieChaseTaskState UC_BossZombie_ChaseTask::GetState(UBehaviorTreeComponent& OwnerComp)
{
    int State = GetBlackBoard(&OwnerComp)->GetValueAsInt(TEXT("TaskState"));
    return static_cast<EBossZombieChaseTaskState>(State);
}

void UC_BossZombie_ChaseTask::SetState(UBehaviorTreeComponent& OwnerComp, EBossZombieChaseTaskState _State)
{
    int State = static_cast<int>(_State);
    GetBlackBoard(&OwnerComp)->SetValueAsInt(TEXT("TaskState"), State);
}

float UC_BossZombie_ChaseTask::GetTimer(UBehaviorTreeComponent& OwnerComp)
{
    return GetBlackBoard(&OwnerComp)->GetValueAsFloat(TEXT("Timer"));
}

void UC_BossZombie_ChaseTask::SetTimer(UBehaviorTreeComponent& OwnerComp, float _Time)
{
    GetBlackBoard(&OwnerComp)->SetValueAsFloat(TEXT("Timer"), _Time);
}

void UC_BossZombie_ChaseTask::AddTimer(UBehaviorTreeComponent& OwnerComp, float _AddTime)
{
    float Timer = GetTimer(OwnerComp);
    SetTimer(OwnerComp, Timer + _AddTime);
}