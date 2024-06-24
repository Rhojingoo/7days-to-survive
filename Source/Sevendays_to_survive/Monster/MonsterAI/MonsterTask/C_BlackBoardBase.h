// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
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

    UPROPERTY()
    uint16 EnemyKeyId;

    UPROPERTY(VisibleAnywhere, Category = "Blackboard")
    AActor* TargetActor = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Blackboard")
    class AC_MonsterAIBase* TaskController = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Blackboard")
    FString TargetActorName;

    UPROPERTY(VisibleAnywhere, Category = "BlackboardKey")
    FString BoolName;

    UPROPERTY(VisibleAnywhere, Category = "BlackboardKey")
    FString WaitTimeName;

    UPROPERTY(VisibleAnywhere, Category = "BlackboardKey")
    UBlackboardComponent* BlackboardComp = nullptr;

    UPROPERTY()
    bool IsInit = false;
};
