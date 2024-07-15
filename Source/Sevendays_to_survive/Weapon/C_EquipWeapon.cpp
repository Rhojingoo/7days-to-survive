// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_EquipWeapon.h"
#include "Weapon/C_GunComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon/Global/DataTable/C_WeaponDataTable.h"
#include "STS/C_STSInstance.h"

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
	SpringArm->TargetArmLength = 0.0f; // The camera follows at this distance behind the character	
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	Cameras = CreateDefaultSubobject<UCameraComponent >(TEXT("GunFollowCamera"));
	Cameras->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void AC_EquipWeapon::PlayGunAnimation_Implementation(const EWeaponUseState _CurWeapon)
{
	switch (_CurWeapon)
	{
	case EWeaponUseState::Rifle2:
		SkeletalMesh->PlayAnimation(WeaponAnimation[_CurWeapon],false);
		break;
	case EWeaponUseState::Pistol2:
		SkeletalMesh->PlayAnimation(WeaponAnimation[_CurWeapon], false);
		break;
	case EWeaponUseState::Shotgun:
		SkeletalMesh->PlayAnimation(WeaponAnimation[_CurWeapon], false);
		break;
	default:
		break;
	}
}

void AC_EquipWeapon::PlayGunAnimationServer_Implementation(const EWeaponUseState _CurWeaon)
{
	PlayGunAnimation(_CurWeaon);
}

// Called when the game starts or when spawned
void AC_EquipWeapon::BeginPlay()
{
	Super::BeginPlay();
	UC_STSInstance* STSInstance = GetWorld()->GetGameInstanceChecked<UC_STSInstance>();

	UAnimationAsset* Rifle2 = STSInstance->GetWeaPonDataTable("Rifle2")->WeaponAnimToPlay;
	WeaponAnimation.Add(EWeaponUseState::Rifle2, Rifle2);

	UAnimationAsset* Pistol2 = STSInstance->GetWeaPonDataTable("Pistol2")->WeaponAnimToPlay;
	WeaponAnimation.Add(EWeaponUseState::Pistol2, Pistol2);

	UAnimationAsset* Shotgun = STSInstance->GetWeaPonDataTable("ShotGun")->WeaponAnimToPlay;
	WeaponAnimation.Add(EWeaponUseState::Shotgun, Shotgun);

}

// Called every frame
void AC_EquipWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

