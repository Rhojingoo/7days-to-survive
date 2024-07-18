// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Animation/C_ReloadMontageNotify.h"
#include "Player/Global/C_GlobalPlayer.h"

UC_ReloadMontageNotify::UC_ReloadMontageNotify()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(200, 0, 0, 255);
	NotifyName = TEXT("Reload_End");
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

	switch (PlayCharacter->GetPlayerCurState())
	{
	case EWeaponUseState::Rifle:
		if (PlayCharacter->Getmagazinecapacity()[ESkerItemSlot::RRifle] != 0)
		{
			return;
		}
		PlayCharacter->Getmagazinecapacity()[ESkerItemSlot::RRifle]= PlayCharacter->GetRiflemagazinecapacity();
		break;
	case EWeaponUseState::Rifle2:
		if (PlayCharacter->Getmagazinecapacity()[ESkerItemSlot::RRifle2] != 0)
		{
			return;
		}
		PlayCharacter->Getmagazinecapacity()[ESkerItemSlot::RRifle2] = PlayCharacter->GetRiflemagazinecapacity();
		break;
	case EWeaponUseState::Pistol:
		if (PlayCharacter->Getmagazinecapacity()[ESkerItemSlot::RPistol] != 0)
		{
			return;
		}
		PlayCharacter->Getmagazinecapacity()[ESkerItemSlot::RPistol] = PlayCharacter->GetPistolmagazinecapacity();
		break;
	case EWeaponUseState::Pistol2:
		if (PlayCharacter->Getmagazinecapacity()[ESkerItemSlot::RPistol2] != 0)
		{
			return;
		}
		PlayCharacter->Getmagazinecapacity()[ESkerItemSlot::RPistol2] = PlayCharacter->GetPistolmagazinecapacity();
		break;
	case EWeaponUseState::Shotgun:
		if (PlayCharacter->Getmagazinecapacity()[ESkerItemSlot::RShotgun] != 0)
		{
			return;
		}
		PlayCharacter->Getmagazinecapacity()[ESkerItemSlot::RShotgun] = PlayCharacter->GetShotGunmagazinecapacity();
		break;
	default:
		break;
	}
}
