// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_MonsterSpawnPoint.h"
#include "Monster/C_ZombieBase.h"

// Sets default values
AC_MonsterSpawnPoint::AC_MonsterSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_MonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_MonsterSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MonsterSpawn(DeltaTime);
}

void AC_MonsterSpawnPoint::MonsterSpawn(float DeltaTime)
{
	CoolTime += DeltaTime;
	if (SpawnTime <= CoolTime) {
	FTransform Transform =	GetActorTransform();
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AC_ZombieBase>(SpawnMonster, Transform, SpawnInfo);
	CoolTime = 0.0f;
	}
}

