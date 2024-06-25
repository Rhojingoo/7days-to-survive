// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_HealthBar.h"


float UC_HealthBar::DecreaseBar(float _Damage) // 감소하는 함수
{

	CurHealth = CurHealth - _Damage;
	return CurHealth;
	
}
float UC_HealthBar::HealBar(float _HealNum) //체력회복 및 값이 올라가는 값
{
	CurHealth = CurHealth + _HealNum;

	return CurHealth;

}

void UC_HealthBar::VisiableHpText() //텍스트를 컨트롤 할 함수
{

}




void UC_HealthBar::SetCurHealth(float _Num)
{
	CurHealth = _Num;
}



void UC_HealthBar::SetMaxHealth(float _Num)
{
	MaxHealth = _Num; //장비를 입을때 마다 값이 늘엊나게 할 생각임 
}