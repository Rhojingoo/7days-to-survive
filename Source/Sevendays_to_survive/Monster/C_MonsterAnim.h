// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_MonsterAnim.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_MonsterAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	template<typename EnumType>
	void ChangeAnimation(EnumType Key)
	{
		ChangeAnimation(static_cast<uint8>(Key));
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

protected:

	// void Init(TArray<TPair<FString, class UAnimMontage*>>);

private:
	// �ؽ����Դϴ�.
	// C++�� ġ�� unordered_map
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<uint8, class UAnimMontage* > AnimMontages;
};
