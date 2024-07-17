// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify_PlaySound.h"
#include "C_SoundNotify.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_SoundNotify : public UAnimNotify_PlaySound
{
	GENERATED_BODY()
	
public:
	UC_SoundNotify();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
