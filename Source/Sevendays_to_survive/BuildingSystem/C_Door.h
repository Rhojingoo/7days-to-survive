// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingSystem/C_BuildingPart.h"
#include "C_Door.generated.h"

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_Door : public AC_BuildingPart
{
	GENERATED_BODY()

public:
	AC_Door();

	UFUNCTION(BlueprintCallable)
	void MapInteract();

	UFUNCTION(BlueprintCallable)
	void Open();

	UFUNCTION(BlueprintCallable)
	void Close();

	UFUNCTION(BlueprintCallable)
	bool IsOpen() const;
private:
	bool IsOpenValue = false;
};

	
