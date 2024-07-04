// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Map/C_MapInteractable.h"
#include "Map/C_Items.h"

#include "C_ItemPouch.generated.h"

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_ItemPouch : public AC_MapInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_ItemPouch();

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure)
	FC_ItemAndCount GetItemAndCount() const;

	UFUNCTION(NetMulticast, Reliable)
	void SetItemAndCount(FName _Id, int _Count);

	void SetItemAndCount_Implementation(FName _Id, int _Count);

	void MapInteract() override;

	void ShowInteractionWidget() override;

	void HideInteractionWidget() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION(BlueprintCallable)
	void DestroyOnServer();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FC_ItemAndCount ItemAndCount;
};
