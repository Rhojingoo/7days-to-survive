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
		//HearingConfig->HearingRange = AIHearingRange; // ���� ���� ����
		//HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
		//HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
		//HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;	    // Ž�� ���� ���ΰ��� �ȿ� ����
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

		//BTC->StartTree(*Monster->AITree);  // ���� �����ϰų� �̹� �������̴� behavior tree�� ���� Ȥ�� ������ϴµ� ����
		RunBehaviorTree(Monster->AITree);  // ��� behavior tree�� �����ϴµ� ���Ǵ� �Լ��̸�, �̹� �����ϴ� tree�� �ٸ� behavior tree�� �����ϰ� �ٲ� ���� ����
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
	//	// �߰ߵ� ������ ��ġ ��������
	//	FVector ActorLocation = Actor->GetActorLocation();

	//	// Blackboard�� ��ġ ����
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
