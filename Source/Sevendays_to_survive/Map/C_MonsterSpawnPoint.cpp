// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_MonsterSpawnPoint.h"
#include "Monster/C_ZombieBase.h"
#include "Components/BoxComponent.h"
#include "STS/C_STSInstance.h"

// Sets default values
AC_MonsterSpawnPoint::AC_MonsterSpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SpawnBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBoxComponent"));
	SpawnBoxComponent->SetupAttachment(RootComponent);
	//SpawnBoxComponent->SetHiddenInGame(false);
	SpawnBoxComponent->SetBoxExtent({ 100.0f, 100.0f, 10.0f });

	CollisionCheckBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionCheckBoxComponent"));
	CollisionCheckBoxComponent->SetupAttachment(RootComponent);
	//CollisionCheckBoxComponent->SetHiddenInGame(false);
	CollisionCheckBoxComponent->SetBoxExtent({ 200.0f, 200.0f, 400.0f });

}

// Called when the game starts or when spawned
void AC_MonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	if (true == HasAuthority()) {
		UC_STSInstance* Inst = Cast<UC_STSInstance>(GetGameInstance());
		Inst->AddSpawnPoint(this);
		if (true == IsBeginSpawnPoint)
		{
			SetSpawn(true);
		}
		/*FTimerHandle ZombieSpawn;
		GetWorld()->GetTimerManager().SetTimer(ZombieSpawn, FTimerDelegate::CreateLambda([&]()
			{
				this->CanSpawn = false;
			}), TotalSpawnTime, false);*/
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
		FTransform Transform;
		Transform.SetScale3D({ 1.0f, 1.0f,1.0f });
		Transform.SetLocation(GetRandomPointInBox());
		FActorSpawnParameters SpawnInfo;
		GetWorld()->SpawnActor<AC_ZombieBase>(SpawnZombie, Transform, SpawnInfo);
		SpawnCount++;
		CoolTime = 0.0f;
	}
	if (SpawnCount == SpawnEndCount)
	{
		this->Destroy();
	}
}

void AC_MonsterSpawnPoint::SetSpawn(bool _IsSpawn)
{
	CanSpawn = true;

	/*FTimerHandle ZombieSpawn;
	GetWorld()->GetTimerManager().SetTimer(ZombieSpawn, FTimerDelegate::CreateLambda([&]()
		{
			this->CanSpawn = false;
		}), TotalSpawnTime, false);*/
}

UClass* AC_MonsterSpawnPoint::ZombieClass()
{
	return SpawnZombie;
}

FVector AC_MonsterSpawnPoint::GetRandomPointInBox() const
{
	if (SpawnBoxComponent)
	{
		FVector Origin;
		FVector BoxExtent;
		BoxExtent = SpawnBoxComponent->GetScaledBoxExtent();
		Origin = SpawnBoxComponent->GetComponentLocation();

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
	FVector BoxExtent = SpawnBoxComponent->GetUnscaledBoxExtent();

	BoxExtent.X = FMath::Max(BoxExtent.X - _ReduceValue.X, 0.0f);
	BoxExtent.Y = FMath::Max(BoxExtent.Y - _ReduceValue.Y, 0.0f);

	SpawnBoxComponent->SetBoxExtent(BoxExtent);
}

void AC_MonsterSpawnPoint::IncreaseZombie()
{
	if (false == IsBoss)
	{
		uint8 IncreaseSpawnCount = SpawnEndCount * 2;
		SpawnEndCount = IncreaseSpawnCount;
	}
}