// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "C_TaskMonsterChase.generated.h"

/**
 *
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_TaskMonsterChase : public UBTTask_BlackboardBase
{
    GENERATED_BODY()
public:
    UC_TaskMonsterChase();
protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UFUNCTION()
    void InitTask(UBehaviorTreeComponent* OwnerComp);

    UPROPERTY()
    AActor* TargetActor = nullptr;

    UPROPERTY()
    uint16 EnemyKeyId;

private:

};
