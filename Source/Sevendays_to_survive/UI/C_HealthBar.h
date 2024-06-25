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
	float DecreasewithObject(UObject* _Collision, float _CurHealth); //오브젝트와 충돌했을경우

	UFUNCTION(BlueprintCallable)
	float DecreasewithActor(AActor* _ACollision, float _CurHealth);

	UFUNCTION(BlueprintCallable)
	void SetCurHealth(float _Num);

	

private:
	float CurHealth = 0.0f;

};
