// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Animation/C_ReloadMontageNotify.h"
#include "Player/Global/C_GlobalPlayer.h"

UC_ReloadMontageNotify::UC_ReloadMontageNotify()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(200, 0, 0, 255);
	NotifyName = TEXT("Hit_End");
#endif // WITH_EDITORONLY_DATA
}

void UC_ReloadMontageNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AC_GlobalPlayer* PlayCharacter = MeshComp->GetOwner<AC_GlobalPlayer>();

	if (nullptr == PlayCharacter)
	{
		return;
	}

	PlayCharacter->ResetHit();
}
