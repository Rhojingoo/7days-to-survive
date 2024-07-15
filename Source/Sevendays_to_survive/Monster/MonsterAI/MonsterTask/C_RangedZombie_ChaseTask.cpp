// Fill out your copyright notice in the Description page of Project Settings.


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

bool UC_RangedZombie_ChaseTask::MonsterRangeTask(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
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

    float RangedAttackTimer = GetBlackBoard(&OwnerComp)->GetValueAsFloat(TEXT("RangedAttackTimer"));
    RangedAttackTimer -= DeltaSeconds;
    GetBlackBoard(&OwnerComp)->SetValueAsFloat(TEXT("RangedAttackTimer"), RangedAttackTimer);

    if (Vec <= MCP->GetData()->GetMonsterRange()
        && RangedAttackTimer <= 0.0f) {
        MonsterData->RemovePath();

        FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(SelfLocation, TargetLocation);
        GetSelf(&OwnerComp)->SetActorRotation(Rotator);

        GetController(&OwnerComp)->GetMCP()->RangedAttack();
        GetBlackBoard(&OwnerComp)->SetValueAsFloat(TEXT("RangedAttackTimer"), RangedAttackCooldown);

        return true;
    }
    else {
        return false;
    }
}