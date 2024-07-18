// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "C_ZombieBullet.generated.h"

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_ZombieBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_ZombieBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetInitialSpeed() const;
	void SetSpawner(AActor* _Actor);

	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UStaticMeshComponent* SMComponent = nullptr;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
	class UAudioComponent* AudioComponent;

	// Function that initializes the projectile's velocity in the shoot direction.
	void SetDirection(const FVector& ShootDirection);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* Spawner = nullptr;

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void SetHitSound();
	void SetHitSound_Implementation();
};
