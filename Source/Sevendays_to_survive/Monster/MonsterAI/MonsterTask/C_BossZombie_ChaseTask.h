// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterAI/MonsterTask/C_TaskMonsterChase.h"
#include "C_BossZombie_ChaseTask.generated.h"

class AC_BossZombie;

UENUM(BlueprintType)
enum class EBossZombieChaseTaskState : uint8
{
    Run,
    Rush,
    Faint
};

UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_BossZombie_ChaseTask : public UC_TaskMonsterChase
{
	GENERATED_BODY()
	
private:

public:
    UC_BossZombie_ChaseTask();
protected:
    bool MonsterRangeTask(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds) override;
    bool MonsterRangeTaskOnRun(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds);
    bool MonsterRangeTaskOnRush(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds);
    bool MonsterRangeTaskOnFaint(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds);

    EBossZombieChaseTaskState GetState(UBehaviorTreeComponent& OwnerComp);
    void SetState(UBehaviorTreeComponent& OwnerComp, EBossZombieChaseTaskState _State);

    float GetTimer(UBehaviorTreeComponent& OwnerComp);
    void SetTimer(UBehaviorTreeComponent& OwnerComp, float _Time);
    void AddTimer(UBehaviorTreeComponent& OwnerComp, float _AddTime);

    const float RushCoolDown = 10.0f;
    const float RushTime = 3.0f;
    const float FaintTime = 6.0f;
};
