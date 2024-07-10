﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_RangedZombie_ChaseTask.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "Monster/MonsterData/MonsterDataRow.h"
#include "Monster/C_RangedZombie.h"

UC_RangedZombie_ChaseTask::UC_RangedZombie_ChaseTask()
{
    NodeName = "RangedZombieChase";
    bNotifyTick = true;
}

EBTNodeResult::Type UC_RangedZombie_ChaseTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

void UC_RangedZombie_ChaseTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    float RangedAttackTimer = GetBlackBoard(&OwnerComp)->GetValueAsFloat(TEXT("RangedAttackTimer"));
    RangedAttackTimer -= DeltaSeconds;
    GetBlackBoard(&OwnerComp)->SetValueAsFloat(TEXT("RangedAttackTimer"), RangedAttackTimer);

    AC_RangedZombie* RangedZombie = Cast<AC_RangedZombie>(GetSelf(&OwnerComp));
    if (false == RangedZombie->IsValidLowLevel())
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    AC_MonsterAIBase* Controller = GetController(&OwnerComp);
    UC_MonsterComponent* MCP = Controller->GetMCP();
    AActor* Target = Cast<AActor>(GetBlackBoard(&OwnerComp)->GetValueAsObject(*TargetActor));
    if (Target->IsValidLowLevel() == false) {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    }


    FVector TargetLocation = Target->GetActorLocation();
    TargetLocation.Z = 0;

    FVector SelfLocation = GetSelfLocationNoneZ(&OwnerComp);

    float Vec = FVector::Dist(SelfLocation, TargetLocation);

    // 근거리 공격
    if (Vec < MeleeAttackDistance && false == RangedZombie->IsRangedAttacking()) {
        GetController(&OwnerComp)->GetMCP()->Attack();
    }
    // 원거리 공격
    else if (Vec < MCP->GetData()->GetMonsterRange() && RangedAttackTimer <= 0.0f) {
        FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(SelfLocation, TargetLocation);
        RangedZombie->SetActorRotation(Rotator);

        GetController(&OwnerComp)->GetMCP()->RangedAttack();
        GetBlackBoard(&OwnerComp)->SetValueAsFloat(TEXT("RangedAttackTimer"), RangedAttackCooldown);
        return;
    }

    if (false == RangedZombie->IsRangedAttacking())
    {
        MCP->Run(Target->GetActorLocation() - SelfLocation);
    }
    return;
}
