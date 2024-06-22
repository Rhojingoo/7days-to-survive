// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_DestructibleHISMA.h"

// Sets default values
AC_DestructibleHISMA::AC_DestructibleHISMA()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HISM = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HierarchicalInstancedStaticMesh"));
	SetRootComponent(HISM);
}

// Called when the game starts or when spawned
void AC_DestructibleHISMA::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_DestructibleHISMA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

