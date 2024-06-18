// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_GlobalAnimInstance.generated.h"

class UAnimMontage;
/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_GlobalAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	void ChangeAnimation(const FString& key);
protected:

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<FString, UAnimMontage*> AnimMontages;
};
