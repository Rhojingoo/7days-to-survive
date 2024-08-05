// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
//#include "Components/StaticMeshComponent.h"
#include "C_GunComponent.generated.h"

class AC_GlobalPlayer;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class SEVENDAYS_TO_SURVIVE_API UC_GunComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AC_NickMainPlayer> ProjectileClass;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	/** MappingContext */
	/** Sets default values for this component's properties */
	UC_GunComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachWeapon(AC_GlobalPlayer* _TargetCharacter, ESkerItemSlot _GunWeapon);



	/** Make the weapon Fire a Projectile */
	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	//void Fire();

protected:
	/** Ends gameplay for this component. */
	//UFUNCTION()
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** The Character holding this weapon*/
	AC_GlobalPlayer* Character = nullptr;
};
