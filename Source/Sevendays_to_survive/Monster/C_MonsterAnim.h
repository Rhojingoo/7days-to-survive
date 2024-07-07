// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Net/UnrealNetwork.h"
#include "C_MonsterAnim.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_MonsterAnim : public UAnimInstance
{
	GENERATED_BODY()

public:

	UC_MonsterAnim();
	template<typename EnumType>
	void ChangeAnimation(EnumType Key)
	{
		ChangeAnimation(static_cast<uint8>(Key));
		//ChangeAnimation_Implementation(static_cast<uint8>(Key));
	}



	void ChangeAnimation(uint8 Key);

	template<typename EnumType>
	void PushAnimation(EnumType Key, class UAnimMontage* _Montage)
	{
		PushAnimation(static_cast<uint8>(Key), _Montage);
	}

	void PushAnimation(uint8 Key, class UAnimMontage* _Montage);

	TMap<uint8, class UAnimMontage* > GetAnimMontages()
	{
		return AnimMontages;
	}

	bool IsPlayMontage();

protected:

	// void Init(TArray<TPair<FString, class UAnimMontage*>>);

private:
	// 해쉬맵입니다.
	// C++로 치면 unordered_map
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<uint8, class UAnimMontage* > AnimMontages;
};
