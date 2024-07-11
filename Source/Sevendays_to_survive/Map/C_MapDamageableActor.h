// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map/C_MapActor.h"
#include "C_MapDamageableActor.generated.h"

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_MapDamageableActor : public AC_MapActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_MapDamageableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
