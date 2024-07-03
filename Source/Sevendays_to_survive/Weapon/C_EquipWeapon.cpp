// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_EquipWeapon.h"
#include "Weapon/C_GunComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AC_EquipWeapon::AC_EquipWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<UC_GunComponent>(TEXT("SkeletalMesh"));
	SetRootComponent(SkeletalMesh);
}

// Called when the game starts or when spawned
void AC_EquipWeapon::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AC_EquipWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

