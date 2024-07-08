// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Notify/C_AttackNotify.h"
#include "Monster/C_ZombieBase.h"

UC_AttackNotify::UC_AttackNotify()
{
	int a = 0;
}

void UC_AttackNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AC_ZombieBase* Zombie = Cast<AC_ZombieBase>(MeshComp->GetOwner());
	if (Zombie->IsValidLowLevel()) {
		Zombie->OnNotifyBegin();
	}
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}
void UC_AttackNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}
void UC_AttackNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AC_ZombieBase* Zombie = Cast<AC_ZombieBase>(MeshComp->GetOwner());
	if (Zombie->IsValidLowLevel()) {
		Zombie->OnNotifyEnd();
	}
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
