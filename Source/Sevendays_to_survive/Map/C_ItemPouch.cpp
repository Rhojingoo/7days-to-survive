// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_ItemPouch.h"

// Sets default values
AC_ItemPouch::AC_ItemPouch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	SetRootComponent(StaticMeshComponent);
}

TMap<FName, int> AC_ItemPouch::GetItems()
{
	return Items;
}

void AC_ItemPouch::SetItems(const TMap<FName, int>& _Items)
{
	Items = _Items;
}

// Called when the game starts or when spawned
void AC_ItemPouch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_ItemPouch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

