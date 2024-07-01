// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_PickUpWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AC_PickUpWeapon::AC_PickUpWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	SetRootComponent(Weapon);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Weapon);
	Sphere->InitSphereRadius(64.0f);
}

// Called when the game starts or when spawned
void AC_PickUpWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_PickUpWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

