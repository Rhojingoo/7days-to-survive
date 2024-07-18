﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_MonsterSpawnPoint.h"
#include "Monster/C_ZombieBase.h"
#include "Components/BoxComponent.h"
#include "STS/C_STSInstance.h"

// Sets default values
AC_MonsterSpawnPoint::AC_MonsterSpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
	//BoxComponent->SetCollisionProfileName("NoCollision");
}

// Called when the game starts or when spawned
void AC_MonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	if (true == HasAuthority()) {
		UC_STSInstance* Inst = Cast<UC_STSInstance>(GetGameInstance());
		Inst->AddSpawnPoint(this);
	}

	SetSpawn(true);
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
		FTransform Transform;
		Transform.SetScale3D({ 1.0f, 1.0f,1.0f });
		Transform.SetLocation(GetRandomPointInBox());
		ReduceSpawnArea({ 20.0f, 20.0f });
		FActorSpawnParameters SpawnInfo;
		GetWorld()->SpawnActor<AC_ZombieBase>(SpawnZombie, Transform, SpawnInfo);
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
		}), TotalSpawnTime, false);
}

UClass* AC_MonsterSpawnPoint::ZombieClass()
{
	return SpawnZombie;
}

FVector AC_MonsterSpawnPoint::GetRandomPointInBox() const
{
	int a = 0;
	if (BoxComponent)
	{
		FVector Origin;
		FVector BoxExtent;
		BoxExtent = BoxComponent->GetScaledBoxExtent();
		Origin = BoxComponent->GetComponentLocation();

		FVector RandomPoint = Origin;
		RandomPoint.X += FMath::FRandRange(-BoxExtent.X, BoxExtent.X);
		RandomPoint.Y += FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y);
		RandomPoint.Z += FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z);

		return RandomPoint;
	}
	return FVector::ZeroVector;
}

void AC_MonsterSpawnPoint::ReduceSpawnArea(FVector2D _ReduceValue)
{
	FVector BoxExtent = BoxComponent->GetScaledBoxExtent();

	BoxExtent.X -= _ReduceValue.X;
	BoxExtent.Y -= _ReduceValue.Y;

	BoxComponent->SetWorldScale3D(BoxExtent);
}