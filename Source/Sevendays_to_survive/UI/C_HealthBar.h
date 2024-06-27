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
	double DecreaseBar(double _Damage);

	UFUNCTION(BlueprintCallable)
	double HealBar(double _HealNum);

	UFUNCTION(BlueprintCallable)
	void SetCurHealth(double _Num);

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(double _Num);


	UFUNCTION(BlueprintCallable)
	double DecreaseObjectHp(AActor* _Object, double _Damage);

	UFUNCTION(BlueprintCallable)
	void SetMaxStamina(double _Num);

	UFUNCTION(BlueprintCallable)
	void CureStamina();

	UFUNCTION(BlueprintCallable)
	void SetStamina(double _Num);



private:
 
	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	double CurHealth = 0;

	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	double CurStamina = 0;

	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	double MaxStatmina;

	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	double MaxHealth = 100;
	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsActing = false; //뛰거나 점프를 했을때 체크 

	float STimer = 0.0f;

};
