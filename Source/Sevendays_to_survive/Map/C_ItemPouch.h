// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_ItemPouch.generated.h"

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_ItemPouch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_ItemPouch();

	UFUNCTION(BlueprintCallable)
	TMap<FName, int> GetItems();

	UFUNCTION(BlueprintCallable)
	void SetItems(const TMap<FName, int>& _Items);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<FName, int> Items;
};
