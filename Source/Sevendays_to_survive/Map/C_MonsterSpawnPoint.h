// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_MonsterSpawnPoint.generated.h"

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_MonsterSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_MonsterSpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MonsterSpawn(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> SpawnMonster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime = 4.0f;

	float CoolTime = 0.0f;
};
