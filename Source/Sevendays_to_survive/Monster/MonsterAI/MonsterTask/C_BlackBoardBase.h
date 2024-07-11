// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Monster/C_ZombieBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "Monster/Component/C_MonsterComponent.h"
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
    AC_MonsterAIBase* GetController(UBehaviorTreeComponent* OwnerComp);
    FVector GetSelfLocationNoneZ(UBehaviorTreeComponent* OwnerComp);
    FVector GetSelfLocation(UBehaviorTreeComponent* OwnerComp);
    FVector GetSelfVelocity(UBehaviorTreeComponent* OwnerComp);
    bool IsPerceptionUpdated(AC_MonsterAIBase* _Controller);

    const FString TargetActor = "TargetActor";
    const FString IsActEnd = "IsActEnd";
    const FString WaitTime = "WaitTime";
    const FString RandomVector = "RandomVector";
    const FString SoundVector = "SoundVector";
    const FString ScreamZombie = "ScreamZombie";
    const FString FollowZombie = "FollowZombie";
    const FString IsInit = "IsInit";
    const FString BreakTime = "BreakTime";
    
    const float Minimum_BreakTime = 5.0f;
    const float Minimum_Distance = 100.f;
    const float Max_Distance = 3000.f;
};
