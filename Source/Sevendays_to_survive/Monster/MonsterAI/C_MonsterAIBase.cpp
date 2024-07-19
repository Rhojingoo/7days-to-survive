// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/C_ZombieBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Player/MainPlayer/C_NickMainPlayer.h"
#include "STS/C_STSInstance.h"
#include "Monster/Component/C_MonsterComponent.h"
#include "Monster/MonsterData/MonsterDataRow.h"
#include "Components/AudioComponent.h"

AC_MonsterAIBase::AC_MonsterAIBase(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer)
{
	{
		BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
		BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
		APC = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
		MCP = CreateDefaultSubobject<UC_MonsterComponent>(TEXT("Monster Component"));
	}

	{
		SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
		SightConfig->SightRadius = 1000.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 500.0f;
		SightConfig->PeripheralVisionAngleDegrees = 90.0f;
		SightConfig->SetMaxAge(1.0f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 900.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
		SightConfig->SetStartsEnabled(true);
	}


	{
		HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
		HearingConfig->HearingRange = 1000.0f;  // 청각 범위 설정
		HearingConfig->DetectionByAffiliation.bDetectEnemies = true;  // 적 팀의 소리 감지 설정
		HearingConfig->DetectionByAffiliation.bDetectNeutrals = false;  // 중립 팀의 소리 감지 설정
		HearingConfig->DetectionByAffiliation.bDetectFriendlies = false;  // 아군 팀의 소리 감지 설정
	}

	APC->ConfigureSense(*HearingConfig);
	APC->SetDominantSense(HearingConfig->GetSenseImplementation());

	// Perception Updated 이벤트 바인딩
	//APC->OnPerceptionUpdated.AddDynamic(this, &AC_MonsterAIBase::OnPerceptionUpdated);


	SetPerceptionComponent(*APC);
	SetGenericTeamId(FGenericTeamId(1));
}

void AC_MonsterAIBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("OnPossess Its Testing Message in USM"));

	Monster = Cast<AC_ZombieBase>(InPawn);

	MCP->SetController(this);
	MCP->SetMonster(Monster);
	MCP->SetData();
	MCP->GetData()->SetOriginPos(Monster->GetActorLocation());
	Monster->SetMCP(MCP);
	//MCP->SetData();

	if (nullptr != Monster && nullptr != Monster->AITree) {


		if (IsValid(SightConfig)) {
			GetPerceptionComponent()->ConfigureSense(*SightConfig);
			GetPerceptionComponent()->SetDominantSense(SightConfig->GetSenseImplementation());
			GetPerceptionComponent()->UpdatePerceptionAllowList(SightConfig->GetSenseID(), true);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Sightconfig Is Not Vaild"));
		}


		BBC->InitializeBlackboard(*(Monster->AITree->BlackboardAsset));
		BBC->SetValueAsObject("SelfActor", GetPawn());
		APC->InitializeComponent();

		//BTC->StartTree(*Monster->AITree);  // 원래 존재하거나 이미 실행중이던 behavior tree를 시작 혹은 재시작하는데 쓰임
		RunBehaviorTree(Monster->AITree);  // 어떠한 behavior tree를 실행하는데 사용되는 함수이며, 이미 실행하던 tree와 다른 behavior tree를 실행하게 바꿀 수도 있음
	}
}


ETeamAttitude::Type AC_MonsterAIBase::GetTeamAttitudeTowards(const AActor& Other) const
{
	Super::GetTeamAttitudeTowards(Other);
	if (const APawn* OtherPawn = Cast<APawn>(&Other)) {	// Actor는 controller를 반환할 수 없음
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController())) { //controller가 Igenericteamagentinterface를 갖고있어야함
			FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();		// id받아와서
			if (GetGenericTeamId() == OtherTeamID) {	 // 같으면 팀
				//UE_LOG(LogTemp, Warning, TEXT("Friend Found"));
				return ETeamAttitude::Friendly;
			}		
			else {										//아니면 적
				//UE_LOG(LogTemp, Warning, TEXT("Enemy Found"));
				return ETeamAttitude::Hostile;
			}
		}
		else {				//캐스팅 안되면 nullptr이라는 것인데 펑
			return ETeamAttitude::Neutral;
		}
	}
	return ETeamAttitude::Neutral;
}
void AC_MonsterAIBase::BeginPlay()
{
	Super::BeginPlay();

	if (APC && SightConfig && HearingConfig)
	{
		UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SightConfig->GetSenseImplementation(), GetPawn());
		APC->OnPerceptionUpdated.AddDynamic(this, &AC_MonsterAIBase::OnSightUpdated);
		//APC->OnTargetPerceptionForgotten.AddDynamic(this, &AC_MonsterAIBase::OffSightUpdated);
		APC->OnPerceptionUpdated.AddDynamic(this, &AC_MonsterAIBase::OnHearingUpdated);
		//APC->OnTargetPerceptionForgotten.AddDynamic(this, &AC_MonsterAIBase::OffHearingUpdated);

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
#ifdef WITH_EDITOR
		DrawDebugSphere(GetWorld(), Actor->GetActorLocation(), 50.0f, 12, FColor::Red, false, 5.0f);
#endif
		FActorPerceptionBlueprintInfo Info;
		PerceptionComponent->GetActorsPerception(Actor, Info);

		for (const auto& Stimulus : Info.LastSensedStimuli)
		{
			//UAISense_Hearing
			if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>() && Stimulus.WasSuccessfullySensed())
			{
				AC_NickMainPlayer* Player = Cast<AC_NickMainPlayer>(Actor);
				if (true == Player->GetIsPlayerDieCpp()) {
					return;
				}
				SetTargetActor(Actor);
				Monster->PlayFindSound();

				APC->SetSenseEnabled(UAISense_Sight::StaticClass(), false);
				break;
			}
		}
	}
}

//void AC_MonsterAIBase::OffSightUpdated(AActor* _ForgotActor)
//{
//	UE_LOG(LogTemp, Warning, TEXT("OffSight"));
//}

void AC_MonsterAIBase::OnHearingUpdated(const TArray<AActor*>& _UpdateActors)
{

	for (AActor* Actor : _UpdateActors)
	{
		// 청각으로 감지한 액터에 대해 처리할 로직 작성
		FActorPerceptionBlueprintInfo Info;
		PerceptionComponent->GetActorsPerception(Actor, Info);	

		for (const auto& Stimulus : Info.LastSensedStimuli)
		{
			if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>() && Stimulus.WasSuccessfullySensed())
			{
				// 소리를 감지한 위치로 이동
				//MoveToLocation(Stimulus.StimulusLocation);	
				BBC->SetValueAsVector(SoundVec, Stimulus.StimulusLocation);
				BBC->SetValueAsObject(Scream_Zombie, Actor);
				IsSound = true;
				UE_LOG(LogTemp, Warning, TEXT("Heard actor: %s at location: %s"), *Actor->GetName(), *Stimulus.StimulusLocation.ToString());
				break;
			}
		}
	}
}

//void AC_MonsterAIBase::OffHearingUpdated(AActor* _ForgotActor)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Forgot sound of actor: %s"), *_ForgotActor->GetName());
//}

void AC_MonsterAIBase::IsFindOff()
{
	BBC->SetValueAsObject(EnemyKeyId, nullptr);
	BBC->SetValueAsObject(Scream_Zombie, nullptr);
	IsFind = false;
	IsSound = false;
	APC->SetSenseEnabled(UAISense_Sight::StaticClass(), true);
}

UC_MonsterComponent* AC_MonsterAIBase::GetMCP()
{
	return MCP;
}

void AC_MonsterAIBase::SetTargetActor(AActor* _Actor)
{
	BBC->SetValueAsObject(EnemyKeyId, _Actor);
	IsFind = true;
}
