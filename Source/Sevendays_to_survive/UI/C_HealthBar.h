// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_HealthBar.generated.h"

/**
 *
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_HealthBar : public UUserWidget
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	float DecreaseBar(float _Damage);

	UFUNCTION(BlueprintCallable)
	float HealBar(float _HealNum);

	UFUNCTION(BlueprintCallable)
	void SetCurHealth(float _Num);

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float _Num);


	UFUNCTION(BlueprintCallable)
	float DecreaseObjectHp(AActor* _Object, float _Damage);

	


private:
 
	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CurHealth = 0.0f;


	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.0f;

};
