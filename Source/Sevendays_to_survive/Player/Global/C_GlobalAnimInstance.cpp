// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Global/C_GlobalAnimInstance.h"

void UC_GlobalAnimInstance::ChangeAnimation(const FString& key)
{
	//this->Montage_Play();

	if (false == AnimMontages.Contains(key))
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == Cap)"), __FUNCTION__, __LINE__);
		return;
	}

	UAnimMontage* Mon = AnimMontages[key];

	if (nullptr == Mon)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == Cap)"), __FUNCTION__, __LINE__);
		return;
	}
	this->Montage_Play(Mon);
}
