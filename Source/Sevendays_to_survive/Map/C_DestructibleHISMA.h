// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "C_DestructibleHISMA.generated.h"

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_DestructibleHISMA : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_DestructibleHISMA();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UHierarchicalInstancedStaticMeshComponent* HISM = nullptr;

public:
	UFUNCTION(NetMulticast, Reliable)
	void DestroyInstance(int _Index);

	void DestroyInstance_Implementation(int _Index);
};
