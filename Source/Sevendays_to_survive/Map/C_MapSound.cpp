// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_MapSound.h"
#include "Engine/GameInstance.h"
#include "STS/C_STSInstance.h"

// Sets default values
AC_MapSound::AC_MapSound()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_MapSound::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_MapSound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AC_MapSound::TimeCheck(float DeltaTime)
{
	static float CheckTime = 0;
	CheckTime += DeltaTime;
	UC_STSInstance* GINS = Cast<UC_STSInstance>(GetGameInstance());
	bool Isday = GINS->IsDay;

	if (Isday)
	{
		if (CheckTime>40.f)
		{
			PlaySound = true;
			CheckTime = 0.f;
		}
		else
		{
			PlaySound = false;
		}
	}
	else
	{
		if (CheckTime > 20.f)
		{
			PlaySound = true;
			CheckTime = 0.f;
		}
		else
		{
			PlaySound = false;
		}
	}
	return PlaySound;
}

