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
	SightConfig->SightRadius = AISightRadius; // �þ� �ݰ� ����
	SightConfig->DetectionByAffiliation.bDetectEnemies = true; // �� Ž�� ����
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false; // �߸� Ž�� ����
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false; // �Ʊ� Ž�� ����
	SightConfig->PeripheralVisionAngleDegrees = AISightDegree; // �þ� ���� ����

	APC->ConfigureSense(*SightConfig);
	APC->SetDominantSense(SightConfig->GetSenseImplementation());

	// �ð� ������ ���� ó���� �Լ� ����
	APC->OnPerceptionUpdated.AddDynamic(this, &AC_MonsterAIBase::OnSightUpdated);

	UAISenseConfig_Hearing* HearingConfig = NewObject<UAISenseConfig_Hearing>();
	HearingConfig->HearingRange = AIHearingRange; // ���� ���� ����
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true; // �� Ž�� ����
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = false; // �߸� Ž�� ����
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = false; // �Ʊ� Ž�� ����

	APC->ConfigureSense(*HearingConfig);
	APC->SetDominantSense(HearingConfig->GetSenseImplementation());

	// û�� ������ ���� ó���� �Լ� ����
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
