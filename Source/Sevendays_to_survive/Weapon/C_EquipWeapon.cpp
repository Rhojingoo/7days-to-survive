// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_EquipWeapon.h"
#include "Weapon/C_GunComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AC_EquipWeapon::AC_EquipWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<UC_GunComponent>(TEXT("SkeletalMesh"));
	SetRootComponent(SkeletalMesh);
	SkeletalMesh->SetCollisionProfileName(TEXT("NoCollision"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("GunCamera"));
	SpringArm->SetupAttachment(SkeletalMesh, *FString("Zoom"));
	//SpringArm->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	Cameras = CreateDefaultSubobject<UCameraComponent >(TEXT("GunFollowCamera"));
	Cameras->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
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

