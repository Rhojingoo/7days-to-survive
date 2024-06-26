// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Monster/C_ZombieBase.h"
#include "C_BlackBoardBase.generated.h"


/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_BlackBoardBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
    UC_BlackBoardBase();
protected:

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UFUNCTION()
    virtual void InitTask(UBehaviorTreeComponent* OwnerComp);

    UBlackboardComponent* GetBlackBoard(UBehaviorTreeComponent* OwnerComp);
    AC_ZombieBase* GetSelf(UBehaviorTreeComponent* OwnerComp);
    class AC_MonsterAIBase* GetController(UBehaviorTreeComponent* OwnerComp);

    const FString TargetActorName = "TargetActor";
    const FString BoolName = "IsActEnd";
    const FString WaitTimeName = "WaitTime";
    const FString RandomVector = "RandomVector";
    const FString BoolInit = "IsInit";
};
