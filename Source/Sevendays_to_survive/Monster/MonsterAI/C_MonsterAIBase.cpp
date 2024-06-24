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
#include "Player/MainPlayer/C_NickMainPlayer.h"


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
		SightConfig->SetMaxAge(1.0f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 900.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->SetStartsEnabled(true);
	}

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
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Sightconfig Is Not Vaild"));
		}


		BBC->InitializeBlackboard(*(Monster->AITree->BlackboardAsset));
		APC->InitializeComponent();

		//BTC->StartTree(*Monster->AITree);  // 원래 존재하거나 이미 실행중이던 behavior tree를 시작 혹은 재시작하는데 쓰임
		RunBehaviorTree(Monster->AITree);  // 어떠한 behavior tree를 실행하는데 사용되는 함수이며, 이미 실행하던 tree와 다른 behavior tree를 실행하게 바꿀 수도 있음
	}
	SetPerceptionComponent(*APC);

}


ETeamAttitude::Type AC_MonsterAIBase::GetTeamAttitudeTowards(const AActor& Other) const
{
	Super::GetTeamAttitudeTowards(Other);
	const AC_NickMainPlayer* Player = Cast<AC_NickMainPlayer>(&Other);
	if (nullptr != Player) {
		return ETeamAttitude::Hostile;
	}
	return ETeamAttitude::Friendly;			//이거 만들긴 했는데, 안쓸 것 같은데...
}

void AC_MonsterAIBase::BeginPlay()
{
	Super::BeginPlay();

	if (APC && SightConfig/* && HearingConfig*/) {
		UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SightConfig->GetSenseImplementation(), GetPawn());
		APC->OnPerceptionUpdated.AddDynamic(this, &AC_MonsterAIBase::OnSightUpdated);
		APC->OnTargetPerceptionForgotten.AddDynamic(this, &AC_MonsterAIBase::OffSightUpdated);
		APC->Activate();
	}


	if (IsValid(APC)) {
		UE_LOG(LogTemp, Warning, TEXT("BeginPlay Its Testing Message in USM"));
	}
}

void AC_MonsterAIBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	APC->RequestStimuliListenerUpdate();

	/*TArray<AActor*> PerceivedActors;
	APC->GetCurrentlyPerceivedActors(SightConfig->GetClass(), PerceivedActors);
	for (AActor* Actor : PerceivedActors) {
		APC->HasAnyCurrentStimulus(*Actor);
	}*/   // 자극 잃어버렸을 때 확인한느 코드인데 아마 안쓸듯
}

void AC_MonsterAIBase::OnSightUpdated(const TArray<AActor*>& _UpdateActors)
{
	if (_UpdateActors.Num() < 1) {
		UE_LOG(LogTemp, Warning, TEXT("NO One"));
	}

	for (AActor* Actor : _UpdateActors)
	{
		DrawDebugSphere(GetWorld(), Actor->GetActorLocation(), 50.0f, 12, FColor::Red, false, 5.0f);
		BBC->SetValueAsObject(EnemyKeyId, Actor);
		IsFind = true;
		APC->SetSenseEnabled(UAISense_Sight::StaticClass(), false);
	}
	UE_LOG(LogTemp, Warning, TEXT("OnSight"));
}

void AC_MonsterAIBase::OffSightUpdated(AActor* _ForgotActor)
{
	UE_LOG(LogTemp, Warning, TEXT("OffSight"));
}