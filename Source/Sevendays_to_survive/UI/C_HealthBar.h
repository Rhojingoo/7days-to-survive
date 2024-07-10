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
	int  DecreaseBar(int  _Damage);

	UFUNCTION(BlueprintCallable)
	int  HealBar(int  _HealNum);

	UFUNCTION(BlueprintCallable)
	void SetCurHealth(int  _Num);

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(int  _Num);


	UFUNCTION(BlueprintCallable)
	int DecreaseObjectHp(AActor* _Object, int  _Damage);

	UFUNCTION(BlueprintCallable)
	void SetMaxStamina(int  _Num);

	UFUNCTION(BlueprintCallable)
	void CureStamina();

	UFUNCTION(BlueprintCallable)
	void SetStamina(int  _Num);



private:
 
	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int  CurHealth = 0;

	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int  CurStamina = 0;

	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int  MaxStatmina;

	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int  MaxHealth = 100;
	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsActing = false; //뛰거나 점프를 했을때 체크 

	float STimer = 0.0f;

};
