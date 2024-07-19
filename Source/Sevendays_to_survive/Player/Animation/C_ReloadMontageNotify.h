// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "Player/Global/C_PlayerEnum.h"
#include "C_ReloadMontageNotify.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_ReloadMontageNotify : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()
public:
	UC_ReloadMontageNotify();
protected:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
