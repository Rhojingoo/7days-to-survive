// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingSystem/C_BuildingPart.h"
#include "C_Door.generated.h"

enum class EDoorState : uint8
{
	Opened,
	Closed,
	Opening,
	Closing,
};

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_Door : public AC_BuildingPart
{
	GENERATED_BODY()

public:
	AC_Door();

	UFUNCTION(BlueprintCallable)
	void MapInteract();

protected:
	UFUNCTION(BlueprintCallable)
	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Tick(float DeltaSeconds) override;

private:
	UFUNCTION(BlueprintCallable)
	void Open();

	UFUNCTION(BlueprintCallable)
	void Close();

	FVector SpawnLocation;

	EDoorState DoorState = EDoorState::Closed;
	float Theta = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float OpenTime = 0.5f;
};

	
