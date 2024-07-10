﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_HealthBar.h"


int  UC_HealthBar::DecreaseBar(int  _Damage) // 감소하는 함수
{

	if (CurHealth < 0)
	{
		CurHealth = 0;
		return CurHealth;
	}
	CurHealth = CurHealth - _Damage;
	return CurHealth;
	
}
int  UC_HealthBar::HealBar(int  _HealNum) //체력회복 및 값이 올라가는 값
{
	CurHealth = CurHealth + _HealNum;

	return CurHealth;

}

int  UC_HealthBar::DecreaseObjectHp(AActor* _Object, int  _Damage)
{
	//여기에 무언가 넣을려고 했는데 필요가 없다.

	CurHealth = CurHealth - _Damage;

	return CurHealth;
}


void UC_HealthBar::CureStamina()
{
	STimer += GetWorld()->GetDeltaSeconds();
	if (CurStamina < MaxStatmina && STimer >=4) 
	{
	
	CurStamina += 10;
	}
	
	if (CurStamina >= MaxStatmina)
	{
		CurStamina = MaxStatmina;
		STimer = 0;
		//풀 충전 되었을때는 
	}
	


}




void UC_HealthBar::SetCurHealth(int  _Num)
{
	CurHealth = _Num;
}

void UC_HealthBar::SetStamina(int  _Num)
{
	CurStamina = _Num;
}

void UC_HealthBar::SetMaxStamina(int  _Num)
{
	MaxStatmina = _Num;	
}


void UC_HealthBar::SetMaxHealth(int  _Num)
{
	MaxHealth = _Num; //장비를 입을때 마다 값이 늘엊나게 할 생각임 
}