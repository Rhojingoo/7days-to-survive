// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map/C_MapInteractable.h"
#include "C_Car.generated.h"

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_Car : public AC_MapInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Car();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MapInteract() override;

	void ShowInteractionWidget() override;

	void HideInteractionWidget() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector MessageRelativeLocation;
};
