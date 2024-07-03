// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_EquipWeapon.generated.h"

class UC_GunComponent;

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:	
	// Called every frame
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UC_GunComponent* SkeletalMesh = nullptr;

};

