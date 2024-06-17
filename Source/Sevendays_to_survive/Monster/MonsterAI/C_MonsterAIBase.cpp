// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "C_MonsterAIBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/C_MonsterBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include <Perception/AISenseConfig_Hearing.h>

AC_MonsterAIBase::AC_MonsterAIBase(const FObjectInitializer& _ObjectInitializer)
{
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
	APC = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
}

void AC_MonsterAIBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AC_MonsterBase* Monster = Cast<AC_MonsterBase>(InPawn);

	if (nullptr != Monster && nullptr != Monster->AITree) {
		BBC->InitializeBlackboard(*(Monster->AITree->BlackboardAsset));

		EnemyKeyId = BBC->GetKeyID("TargetActorLcation");

		//BBC->SetValueAsObject()
		BTC->StartTree(*Monster->AITree);

	}
}

void AC_MonsterAIBase::BeginPlay()
{
	UAISenseConfig_Sight* SightConfig = NewObject<UAISenseConfig_Sight>();
	SightConfig->SightRadius = AISightRadius; // 시야 반경 설정
	SightConfig->DetectionByAffiliation.bDetectEnemies = true; // 적 탐지 설정
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false; // 중립 탐지 설정
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false; // 아군 탐지 설정
	SightConfig->PeripheralVisionAngleDegrees = AISightDegree; // 시야 각도 설정

	APC->ConfigureSense(*SightConfig);
	APC->SetDominantSense(SightConfig->GetSenseImplementation());

	// 시각 감지에 대한 처리기 함수 설정
	APC->OnPerceptionUpdated.AddDynamic(this, &AC_MonsterAIBase::OnSightUpdated);

	UAISenseConfig_Hearing* HearingConfig = NewObject<UAISenseConfig_Hearing>();
	HearingConfig->HearingRange = AIHearingRange; // 감지 범위 설정
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true; // 적 탐지 설정
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = false; // 중립 탐지 설정
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = false; // 아군 탐지 설정

	APC->ConfigureSense(*HearingConfig);
	APC->SetDominantSense(HearingConfig->GetSenseImplementation());

	// 청각 감지에 대한 처리기 함수 설정
	APC->OnPerceptionUpdated.AddDynamic(this, &AC_MonsterAIBase::OnHearingUpdated);

}

void AC_MonsterAIBase::OnSightUpdated(const TArray<AActor*> & _UpdateActors)
{
	UE_LOG(LogTemp, Warning, TEXT("OnSight"));
}

void AC_MonsterAIBase::OnHearingUpdated(const TArray<AActor*>& _UpdateActors)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHearing"));
}
