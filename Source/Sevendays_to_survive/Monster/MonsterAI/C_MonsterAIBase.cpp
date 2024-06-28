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
#include "Monster/Component/C_MonsterComponent.h"

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
	SetGenericTeamId(FGenericTeamId(1));
}

void AC_MonsterAIBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("OnPossess Its Testing Message in USM"));

	Monster = Cast<AC_ZombieBase>(InPawn);

	MCP->SetController(this);
	MCP->SetMonster(Monster);

	if (nullptr != Monster && nullptr != Monster->AITree) {


		if (IsValid(SightConfig)) {
			APC->ConfigureSense(*SightConfig);
			APC->SetDominantSense(SightConfig->GetSenseImplementation());
			APC->UpdatePerceptionAllowList(SightConfig->GetSenseID(), true);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Sightconfig Is Not Vaild"));
		}


		BBC->InitializeBlackboard(*(Monster->AITree->BlackboardAsset));
		BBC->SetValueAsObject("SelfActor", GetPawn());
		APC->InitializeComponent();

		//BTC->StartTree(*Monster->AITree);  // ���� �����ϰų� �̹� �������̴� behavior tree�� ���� Ȥ�� ������ϴµ� ����
		RunBehaviorTree(Monster->AITree);  // ��� behavior tree�� �����ϴµ� ���Ǵ� �Լ��̸�, �̹� �����ϴ� tree�� �ٸ� behavior tree�� �����ϰ� �ٲ� ���� ����
	}
	SetPerceptionComponent(*APC);

}


ETeamAttitude::Type AC_MonsterAIBase::GetTeamAttitudeTowards(const AActor& Other) const
{
	Super::GetTeamAttitudeTowards(Other);
	if (const APawn* OtherPawn = Cast<APawn>(&Other)) {	// Actor�� controller�� ��ȯ�� �� ����
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController())) { //controller�� Igenericteamagentinterface�� �����־����
			FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();		// id�޾ƿͼ�
			if (GetGenericTeamId() == OtherTeamID) {	 // ������ ��
				UE_LOG(LogTemp, Warning, TEXT("Friend Found"));
				return ETeamAttitude::Neutral;
			}		
			else {										//�ƴϸ� ��
				UE_LOG(LogTemp, Warning, TEXT("Enemy Found"));
				return ETeamAttitude::Hostile;
			}
		}
		else {				//ĳ���� �ȵǸ� nullptr�̶�� ���ε� ��
			UE_LOG(LogTemp, Fatal, TEXT("Boom"));
		}
	}
	return ETeamAttitude::Neutral;
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
	}*/   // �ڱ� �Ҿ������ �� Ȯ���Ѵ� �ڵ��ε� �Ƹ� �Ⱦ���
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
		break;
	}
	UE_LOG(LogTemp, Warning, TEXT("OnSight"));
}

void AC_MonsterAIBase::OffSightUpdated(AActor* _ForgotActor)
{
	UE_LOG(LogTemp, Warning, TEXT("OffSight"));
}

UC_MonsterComponent* AC_MonsterAIBase::GetMCP()
{
	return MCP;
}
