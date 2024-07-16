// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/Global/C_PlayerEnum.h"
#include "C_EquipWeapon.generated.h"

class UC_GunComponent;
class USpringArmComponent;
class UCameraComponent;
class UParticleSystem;
struct FC_WeaponDataTable;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_EquipWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AC_EquipWeapon();

	UFUNCTION()
	UC_GunComponent* GetWeaponMesh()
	{
		return SkeletalMesh;
	}

	UFUNCTION(Reliable, NetMulticast)
	void PlayGunAnimation(const EWeaponUseState _CurWeaon);
	void PlayGunAnimation_Implementation(const EWeaponUseState _CurWeaon);

	UFUNCTION(Reliable, NetMulticast)
	void GunParticleAndSound(const EWeaponUseState _CurWeaon);
	void GunParticleAndSound_Implementation(const EWeaponUseState _CurWeaon);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// Called every frame
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UC_GunComponent* SkeletalMesh = nullptr;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Cameras = nullptr;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<EWeaponUseState, UAnimationAsset*> WeaponAnimation;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap <EWeaponUseState,UParticleSystem*> ShotEffects;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap <EWeaponUseState,USoundBase*> ShotSounds;
};

