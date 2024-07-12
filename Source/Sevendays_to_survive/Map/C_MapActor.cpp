// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_MapActor.h"

// Sets default values
AC_MapActor::AC_MapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AC_MapActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_MapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

