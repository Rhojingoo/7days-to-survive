// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "C_BlackBoardBase.h"
#include "C_TaskMonsterChase.generated.h"

/**
 *
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_TaskMonsterChase : public UC_BlackBoardBase
{
    GENERATED_BODY()
public:
    UC_TaskMonsterChase();

    bool SetPath(FVector _MyLocation, FVector _TargetLocation, class UMonsterDataObject* _Data, UBlackboardComponent* _BBC);
    bool NaviMove(UMonsterDataObject* _Data, UBlackboardComponent* _BBC, AAIController* _Controller, UBehaviorTreeComponent& OwnerComp, float _TargetDistance);
    bool MonsterAttack(UMonsterDataObject* _Data, AAIController* _Controller, float _Distance);
    bool MonsterNaviTime(float _DeltaTime, UBlackboardComponent* _BBC);
    void ResetNaviTime(UBlackboardComponent* _BBC);

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    void InitTask(UBehaviorTreeComponent* OwnerComp) override;

    void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

    virtual bool MonsterRangeTask(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds);
private:

};
