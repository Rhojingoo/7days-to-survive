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
		SightConfig->SightRadius = 1000.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 500.0f;
		SightConfig->PeripheralVisionAngleDegrees = 90.0f;
		SightConfig->SetMaxAge(5.0f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 900.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->SetStartsEnabled(true);

		//HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
		//HearingConfig->HearingRange = AIHearingRange; // 감지 범위 설정
		//HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
		//HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
		//HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;	    // 탐지 설정 세부값은 안에 보기
		//HearingConfig->SetMaxAge(1.0f);
		//HearingConfig->SetStartsEnabled(true);
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
			APC->ConfigureSense(*SightConfig);
			APC->SetDominantSense(SightConfig->GetSenseImplementation());
			APC->UpdatePerceptionWhitelist(SightConfig->GetSenseID(), true);

			//APC->ConfigureSense(*HearingConfig);

		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Sightconfig Is Not Vaild"));
		}



		//if (IsValid(HearingConfig)) {
		//}
		//else {
		//	UE_LOG(LogTemp, Warning, TEXT("Hearing Config Is Not Vaild"));
		//}
		BBC->InitializeBlackboard(*(Monster->AITree->BlackboardAsset));

		EnemyKeyId = BBC->GetKeyID("TargetActor");

		//BTC->StartTree(*Monster->AITree);  // 원래 존재하거나 이미 실행중이던 behavior tree를 시작 혹은 재시작하는데 쓰임
		RunBehaviorTree(Monster->AITree);  // 어떠한 behavior tree를 실행하는데 사용되는 함수이며, 이미 실행하던 tree와 다른 behavior tree를 실행하게 바꿀 수도 있음
	}

}

void AC_MonsterAIBase::BeginPlay()
{
	Super::BeginPlay();

	if (APC && SightConfig/* && HearingConfig*/){
		UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SightConfig->GetSenseImplementation(), GetPawn());
		//UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, HearingConfig->GetSenseImplementation(), GetPawn());

		APC->OnPerceptionUpdated.AddDynamic(this, &AC_MonsterAIBase::OnSightUpdated);
		APC->OnTargetPerceptionForgotten.AddDynamic(this, &AC_MonsterAIBase::OffSightUpdated);
		//APC->OnPerceptionUpdated.AddDynamic(this, &AC_MonsterAIBase::OnHearingUpdated);
		//APC->OnTargetPerceptionForgotten.AddDynamic(this, &AC_MonsterAIBase::OffHearingUpdated);
		APC->Activate();
	}


	if (IsValid(APC)) {
		UE_LOG(LogTemp, Warning, TEXT("BeginPlay Its Testing Message in USM"));
	}
	//APC->SetSenseEnabled(SightConfig->GetClass(), true);
}

void AC_MonsterAIBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	APC->RequestStimuliListenerUpdate();
	//if (!IsValid(HearingConfig)) {
	//	UE_LOG(LogTemp, Warning, TEXT("Hearing not Vaild Testing log"));
	//}
}

void AC_MonsterAIBase::OnSightUpdated(const TArray<AActor*>& _UpdateActors)
{
	
	for (AActor* Actor : _UpdateActors)
	{
		DrawDebugSphere(GetWorld(), Actor->GetActorLocation(), 50.0f, 12, FColor::Red, false, 5.0f);
		//BBC->SetValueAsObject(TEXT("TargetActor"), Actor);
		FActorPerceptionBlueprintInfo Info;
		APC->GetActorsPerception(Actor, Info);

		for (const FAIStimulus& Stimulus : Info.LastSensedStimuli) {
			if (Stimulus.Type == SightConfig->GetSenseID()) {
			}
		}
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

//void AC_MonsterAIBase::OnHearingUpdated(const TArray<AActor*>& _UpdateActors)
//{

	//for (AActor* Actor : _UpdateActors)
	//{
	//	FActorPerceptionBlueprintInfo Info;
	//	APC->GetActorsPerception(Actor, Info);

	//	for (const FAIStimulus& Stimulus : Info.LastSensedStimuli) {
	//		if (Stimulus.Type == HearingConfig->GetSenseID()) {
	//			UE_LOG(LogTemp, Warning, TEXT("OnHearing"));
	//		}
	//	}
	//}

//}

//void AC_MonsterAIBase::OffHearingUpdated(AActor* _ForgotActor)
//{
//	UE_LOG(LogTemp, Warning, TEXT("OffHearing"));
//}
