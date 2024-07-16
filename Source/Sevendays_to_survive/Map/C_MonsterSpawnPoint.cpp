// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_MonsterSpawnPoint.h"
#include "Monster/C_ZombieBase.h"
#include "STS/C_STSInstance.h"

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
	if (true == HasAuthority()) {
		UC_STSInstance* Inst = Cast<UC_STSInstance>(GetGameInstance());
		Inst->AddSpawnPoint(this);
	}
}

// Called every frame
void AC_MonsterSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (true == CanSpawn) {
		if (true == HasAuthority()) {
			MonsterSpawn(DeltaTime);
		}
	}
}

void AC_MonsterSpawnPoint::MonsterSpawn(float DeltaTime)
{
	CoolTime += DeltaTime;
	if (SpawnTime <= CoolTime) {
		FTransform Transform = GetActorTransform(); //random location적용 해야 함
		FActorSpawnParameters SpawnInfo;
		GetWorld()->SpawnActor<AC_ZombieBase>(SpawnMonster, Transform, SpawnInfo);
		CoolTime = 0.0f;
	}
}

void AC_MonsterSpawnPoint::SetSpawn(bool _IsSpawn)
{
	CanSpawn = true;

	FTimerHandle ZombieSpawn;
	GetWorld()->GetTimerManager().SetTimer(ZombieSpawn, FTimerDelegate::CreateLambda([&]()
		{
			this->CanSpawn = false;
		}), 20.0f, false);
}



