// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "C_MonsterAIBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/C_MonsterBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"


AC_MonsterAIBase::AC_MonsterAIBase(const FObjectInitializer& _ObjectInitializer)
{
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
	APC = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
}

void AC_MonsterAIBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("OnPossess Its Testing Message in USM"));

	AC_MonsterBase* Monster = Cast<AC_MonsterBase>(InPawn);

	if (nullptr != Monster && nullptr != Monster->AITree) {
		BBC->InitializeBlackboard(*(Monster->AITree->BlackboardAsset));

		EnemyKeyId = BBC->GetKeyID("TargetActorLcation");

		BTC->StartTree(*Monster->AITree);

	}
}

void AC_MonsterAIBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(APC)) {
		UE_LOG(LogTemp, Warning, TEXT("BeginPlay Its Testing Message in USM"));
		UAISenseConfig_Sight* SightConfig = NewObject<UAISenseConfig_Sight>();
		SightConfig->SightRadius = AISightRadius; // �þ� �ݰ� ����
		SightConfig->PeripheralVisionAngleDegrees = AISightDegree; // �þ� ���� ����
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		APC->ConfigureSense(*SightConfig);
		APC->SetDominantSense(SightConfig->GetSenseImplementation());

		// �ð� ������ ���� ó���� �Լ� ����
		APC->OnPerceptionUpdated.AddDynamic(this, &AC_MonsterAIBase::OnSightUpdated);

		UAISenseConfig_Hearing* HearingConfig = NewObject<UAISenseConfig_Hearing>();
		HearingConfig->HearingRange = AIHearingRange; // ���� ���� ����
		HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
		HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
		HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;	    // Ž�� ���� ���ΰ��� �ȿ� ����

		APC->ConfigureSense(*HearingConfig);
		APC->SetDominantSense(HearingConfig->GetSenseImplementation());

		// û�� ������ ���� ó���� �Լ� ����
		APC->OnPerceptionUpdated.AddDynamic(this, &AC_MonsterAIBase::OnHearingUpdated);

	}
}

void AC_MonsterAIBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("OnTick Testing log"));
}

void AC_MonsterAIBase::OnSightUpdated(const TArray<AActor*>& _UpdateActors)
{
	UE_LOG(LogTemp, Warning, TEXT("OnSight"));

	for (AActor* Actor : _UpdateActors)
	{
		if (Actor && APC)
		{
			// �߰ߵ� ������ ��ġ ��������
			FVector ActorLocation = Actor->GetActorLocation();

			// Blackboard�� ��ġ ����
			if (BBC && EnemyKeyId != -1)
			{
				BBC->SetValueAsVector(BBC->GetKeyName(EnemyKeyId), ActorLocation);
			}
		}
	}
}

void AC_MonsterAIBase::OnHearingUpdated(const TArray<AActor*>& _UpdateActors)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHearing"));
}
