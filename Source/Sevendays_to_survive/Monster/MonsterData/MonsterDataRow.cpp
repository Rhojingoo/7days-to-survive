// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterData/MonsterDataRow.h"

void UMonsterDataObject::MonsterDataInit(const FMonsterDataRow& Row)
{
	Att = Row.Att;
	HP = Row.HP;
	MonsterRange = Row.MonsterRange;
}
