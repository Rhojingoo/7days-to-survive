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
			SightConfig->SightRadius = AISightRadius; // �þ� �ݰ� ����
			SightConfig->PeripheralVisionAngleDegrees = AISightDegree; // �þ� ���� ����
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
			HearingConfig->HearingRange = AIHearingRange; // ���� ���� ����
			HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
			HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
			HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;	    // Ž�� ���� ���ΰ��� �ȿ� ����
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

		//BTC->StartTree(*Monster->AITree);  // ���� �����ϰų� �̹� �������̴� behavior tree�� ���� Ȥ�� ������ϴµ� ����
		RunBehaviorTree(Monster->AITree);  // ��� behavior tree�� �����ϴµ� ���Ǵ� �Լ��̸�, �̹� �����ϴ� tree�� �ٸ� behavior tree�� �����ϰ� �ٲ� ���� ����

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
