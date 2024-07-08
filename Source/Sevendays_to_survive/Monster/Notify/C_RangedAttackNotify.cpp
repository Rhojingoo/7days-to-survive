// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Notify/C_RangedAttackNotify.h"
#include "Monster/C_RangedZombie.h"

void UC_RangedAttackNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AC_RangedZombie* Zombie = Cast<AC_RangedZombie>(MeshComp->GetOwner());
	if (Zombie->IsValidLowLevel()) {
		Zombie->OnRangedAttackNotifyBegin();
	}
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void UC_RangedAttackNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AC_RangedZombie* Zombie = Cast<AC_RangedZombie>(MeshComp->GetOwner());
	if (Zombie->IsValidLowLevel()) {
		Zombie->OnRangedAttackNotifyEnd();
	}
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
