// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Notify/C_SoundNotify.h"
#include "STS/C_STSInstance.h"
#include "Monster/MonsterData/MonsterDataRow.h"
#include "Monster/C_ZombieBase.h"
#include "Monster/C_MonsterAnim.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

UC_SoundNotify::UC_SoundNotify()
{

}

void UC_SoundNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AC_ZombieBase* Zombie = Cast<AC_ZombieBase>(MeshComp->GetOwner());
	if (nullptr == Zombie)
	{
		return;
	}

	UC_STSInstance* Inst = Cast<UC_STSInstance>(Zombie->GetGameInstance());

	FString MonsterName = Zombie->GetName();

	FMonsterDataRow* Row = Inst->GetMonsterData(*(MonsterName));
	if (nullptr == Row)
	{
		return;
	}

	uint8 MonsterStateKey = 0;

	UC_MonsterAnim* MonsterAnimInstance = Cast<UC_MonsterAnim>(MeshComp->GetAnimInstance());

	MonsterStateKey = MonsterAnimInstance->GetAnimMontageKey();

	USoundWave** SoundWavePtr = Row->SoundFile.Find(MonsterStateKey);
  	if (nullptr != SoundWavePtr)
	{
		if (nullptr == *SoundWavePtr)
		{
			return;
		}

		Zombie->AudioComponent->SetSound(*SoundWavePtr);
		Zombie->AudioComponent->Play();
		//UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), *SoundWavePtr, MeshComp->GetComponentLocation());
	}
}