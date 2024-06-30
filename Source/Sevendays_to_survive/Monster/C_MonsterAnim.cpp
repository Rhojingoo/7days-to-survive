// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_MonsterAnim.h"

void UC_MonsterAnim::ChangeAnimation(uint8 Key)
{
	if (false == AnimMontages.Contains(Key))
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (false == AnimMontages.Contains(Key))"), __FUNCTION__, __LINE__);
		return;
	}

	UAnimMontage* Mon = AnimMontages[Key];

	// 이렇게 터트리지 않으면 
	if (nullptr == Mon)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == Mon)"), __FUNCTION__, __LINE__);
		return;
	}

	UAnimMontage* PrevMon = GetCurrentActiveMontage();

	if (PrevMon != Mon)
	{
		Montage_Play(Mon);
	}
}

void UC_MonsterAnim::PushAnimation(uint8 Key, class UAnimMontage* _Montage)
{
	if (true == AnimMontages.Contains(Key))
	{
		return;
	}

	AnimMontages.Add(Key, _Montage);
}