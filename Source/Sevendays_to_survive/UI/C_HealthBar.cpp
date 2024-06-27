// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_HealthBar.h"


double UC_HealthBar::DecreaseBar(double _Damage) // �����ϴ� �Լ�
{

	if (CurHealth < 0)
	{
		CurHealth = 0;
		return CurHealth;
	}
	CurHealth = CurHealth - _Damage;
	return CurHealth;
	
}
double UC_HealthBar::HealBar(double _HealNum) //ü��ȸ�� �� ���� �ö󰡴� ��
{
	CurHealth = CurHealth + _HealNum;

	return CurHealth;

}

double UC_HealthBar::DecreaseObjectHp(AActor* _Object, double _Damage)
{
	//���⿡ ���� �������� �ߴµ� �ʿ䰡 ����.

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
		//Ǯ ���� �Ǿ������� 
	}
	


}




void UC_HealthBar::SetCurHealth(double _Num)
{
	CurHealth = _Num;
}

void UC_HealthBar::SetStamina(double _Num)
{
	CurStamina = _Num;
}

void UC_HealthBar::SetMaxStamina(double _Num)
{
	MaxStatmina = _Num;	
}


void UC_HealthBar::SetMaxHealth(double _Num)
{
	MaxHealth = _Num; //��� ������ ���� ���� �þ����� �� ������ 
}