// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterAI/MonsterTask/C_BlackBoardBase.h"
#include "C_BossZombie_ChaseTask.generated.h"

class AC_BossZombie;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_BossZombie_ChaseTask : public UC_BlackBoardBase
{
	GENERATED_BODY()
	
private:
    enum class ETaskState
    {
        Run,
        Rush,
        RushWait
    };

public:
    UC_BossZombie_ChaseTask();
protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

    void OnRunStart();
    void OnRunTick(float DeltaSeconds);
    void OnRunEnd();

    void OnRushStart();
    void OnRushTick(float DeltaSeconds);
    void OnRushEnd();
    
    void OnRushWaitStart();
    void OnRushWaitTick(float DeltaSeconds);
    void OnRushWaitEnd();

    AC_BossZombie* BossZombie = nullptr;
    AActor* Target = nullptr;

    FVector RushDirection = FVector::ZeroVector;
    
    const float RunTime = 5.0f;
    const float RushTime = 3.0f;
    const float RushWaitTime = 6.0f;

    ETaskState TaskState = ETaskState::Run;
    bool IsFirstTick = true;
};
