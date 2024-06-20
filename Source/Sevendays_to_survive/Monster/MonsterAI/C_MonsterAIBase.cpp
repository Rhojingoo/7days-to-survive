// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "C_MonsterAIBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/C_ZombieBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"


AC_MonsterAIBase::AC_MonsterAIBase(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer)
{
	{
		BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
		BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
		APC = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	}

	{
		SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
		HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	}

	EnemyKeyId = 0;
}

void AC_MonsterAIBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("OnPossess Its Testing Message in USM"));

	AC_ZombieBase* Monster = Cast<AC_ZombieBase>(InPawn);

	if (nullptr != Monster && nullptr != Monster->AITree) {

		if (IsValid(SightConfig)) {
			SightConfig->SightRadius = AISightRadius; // 시야 반경 설정
			SightConfig->PeripheralVisionAngleDegrees = AISightDegree; // 시야 각도 설정
			SightConfig->DetectionByAffiliation.bDetectEnemies = true;
			SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
			SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
			SightConfig->SetMaxAge(1.0f);
			SightConfig->SetStartsEnabled(true);
			APC->ConfigureSense(*SightConfig);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Sightconfig Is Not Vaild"));
		}

		if (IsValid(HearingConfig)) {
			HearingConfig->HearingRange = AIHearingRange; // 감지 범위 설정
			HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
			HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
			HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;	    // 탐지 설정 세부값은 안에 보기
			HearingConfig->SetMaxAge(1.0f);
			HearingConfig->SetStartsEnabled(true);
			APC->ConfigureSense(*HearingConfig);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Hearing Config Is Not Vaild"));
		}

		APC->SetDominantSense(SightConfig->GetSenseImplementation());
		APC->OnPerceptionUpdated.AddDynamic(this, &AC_MonsterAIBase::OnSightUpdated);
		APC->OnTargetPerceptionForgotten.AddDynamic(this, &AC_MonsterAIBase::OffSightUpdated);
		APC->OnPerceptionUpdated.AddDynamic(this, &AC_MonsterAIBase::OnHearingUpdated);
		APC->OnTargetPerceptionForgotten.AddDynamic(this, &AC_MonsterAIBase::OffHearingUpdated);


		BBC->InitializeBlackboard(*(Monster->AITree->BlackboardAsset));

		EnemyKeyId = BBC->GetKeyID("TargetActor");

		//BTC->StartTree(*Monster->AITree);  // 원래 존재하거나 이미 실행중이던 behavior tree를 시작 혹은 재시작하는데 쓰임
		RunBehaviorTree(Monster->AITree);  // 어떠한 behavior tree를 실행하는데 사용되는 함수이며, 이미 실행하던 tree와 다른 behavior tree를 실행하게 바꿀 수도 있음

	}

}

void AC_MonsterAIBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(APC)) {

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay Its Testing Message in USM"));


	}
}

void AC_MonsterAIBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("OnTick Testing log"));
	//APC->GetSenseConfig(HearingConfig->GetSenseID());
}

void AC_MonsterAIBase::OnSightUpdated(const TArray<AActor*>& _UpdateActors)
{
	/*for (AActor* Actor : _UpdateActors)
	{
		BBC->SetValueAsObject(TEXT("TargetActor"), Actor);
		FActorPerceptionBlueprintInfo Info;
		APC->GetActorsPerception(Actor, Info);

		for (const FAIStimulus& Stimulus : Info.LastSensedStimuli) {
			if (Stimulus.Type == SightConfig->GetSenseID()) {
			}
		}
	}*/

	if (_UpdateActors.Num() < 1) {
		UE_LOG(LogTemp, Warning, TEXT("offsight"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("OnSight"));
	//	// 발견된 엑터의 위치 가져오기
	//	FVector ActorLocation = Actor->GetActorLocation();

	//	// Blackboard에 위치 저장
	//	if (BBC && EnemyKeyId != -1)
	//	{
	//		BBC->SetValueAsVector(BBC->GetKeyName(EnemyKeyId), ActorLocation);
	//	}
	//}
}

void AC_MonsterAIBase::OffSightUpdated(AActor* _ForgotActor)
{
	UE_LOG(LogTemp, Warning, TEXT("OffSight"));
}

void AC_MonsterAIBase::OnHearingUpdated(const TArray<AActor*>& _UpdateActors)
{

	for (AActor* Actor : _UpdateActors)
	{
		FActorPerceptionBlueprintInfo Info;
		APC->GetActorsPerception(Actor, Info);

		for (const FAIStimulus& Stimulus : Info.LastSensedStimuli) {
			if (Stimulus.Type == HearingConfig->GetSenseID()) {
				UE_LOG(LogTemp, Warning, TEXT("OnHearing"));
			}
		}
	}

}

void AC_MonsterAIBase::OffHearingUpdated(AActor* _ForgotActor)
{
	UE_LOG(LogTemp, Warning, TEXT("OffHearing"));
}
