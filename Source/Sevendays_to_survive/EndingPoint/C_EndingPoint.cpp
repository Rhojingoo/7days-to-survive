// Fill out your copyright notice in the Description page of Project Settings.

#include "EndingPoint/C_EndingPoint.h"
#include "Sevendays_to_survive.h"
//#include "C_EndingPoint.h"

// Sets default values
AC_EndingPoint::AC_EndingPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	//bReplicates = true;
}

// Called when the game starts or when spawned
void AC_EndingPoint::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AC_EndingPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AC_EndingPoint::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//	DOREPLIFETIME(AC_EndingPoint, GoalPos);
//}

