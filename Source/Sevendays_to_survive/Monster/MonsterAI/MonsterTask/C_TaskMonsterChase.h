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
protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    void InitTask(UBehaviorTreeComponent* OwnerComp) override;

    void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

private:

};
