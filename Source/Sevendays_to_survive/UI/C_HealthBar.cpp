// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_HealthBar.h"


float UC_HealthBar::DecreaseBar(float _Damage) // �����ϴ� �Լ�
{

	CurHealth = CurHealth - _Damage;
	return CurHealth;
	
}
float UC_HealthBar::HealBar(float _HealNum) //ü��ȸ�� �� ���� �ö󰡴� ��
{
	CurHealth = CurHealth + _HealNum;

	return CurHealth;

}

void UC_HealthBar::VisiableHpText() //�ؽ�Ʈ�� ��Ʈ�� �� �Լ�
{

}




void UC_HealthBar::SetCurHealth(float _Num)
{
	CurHealth = _Num;
}



void UC_HealthBar::SetMaxHealth(float _Num)
{
	MaxHealth = _Num; //��� ������ ���� ���� �þ����� �� ������ 
}