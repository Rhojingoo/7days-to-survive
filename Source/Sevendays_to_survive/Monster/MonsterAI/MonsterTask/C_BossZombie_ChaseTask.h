// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterAI/MonsterTask/C_BlackBoardBase.h"
#include "C_BossZombie_ChaseTask.generated.h"

class AC_BossZombie;

UENUM(BlueprintType)
enum class EBossZombieChaseTaskState : uint8
{
    Run,
    Rush,
    RushWait
};

UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_BossZombie_ChaseTask : public UC_BlackBoardBase
{
	GENERATED_BODY()
	
private:

public:
    UC_BossZombie_ChaseTask();
protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

    void OnRunStart(UBehaviorTreeComponent& OwnerComp);
    void OnRunTick(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds);
    void OnRunEnd(UBehaviorTreeComponent* OwnerComp);

    void OnRushStart(UBehaviorTreeComponent& OwnerComp);
    void OnRushTick(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds);
    void OnRushEnd(UBehaviorTreeComponent* OwnerComp);
    
    void OnRushWaitStart(UBehaviorTreeComponent& OwnerComp);
    void OnRushWaitTick(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds);
    void OnRushWaitEnd(UBehaviorTreeComponent* OwnerComp);

    const float RunTime = 5.0f;
    const float RushTime = 3.0f;
    const float RushWaitTime = 6.0f;
};
