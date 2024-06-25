// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_HealthBar.h"


float UC_HealthBar::DecreasewithObject(UObject* _Collision, float _CurHealth)
{


	return CurHealth;
	
}
float UC_HealthBar::DecreasewithActor(AActor* _ACollision, float _CurHealth)
{

	return CurHealth;

}

void UC_HealthBar::SetCurHealth(float _Num)
{
	CurHealth = _Num;
}
