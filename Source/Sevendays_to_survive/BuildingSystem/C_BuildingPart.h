// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map/C_MapActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "C_BuildingPart.generated.h"

class UC_HealthBar;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_BuildingPart : public AC_MapActor
{
	GENERATED_BODY()
	
public:
	AC_BuildingPart();

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(NetMulticast, Reliable)
	void ReceiveDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	void ReceiveDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void UpdateHpBar();

	UFUNCTION(BlueprintCallable)
	void HideHpBar();

protected:
	void BeginPlay() override;

private:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Hp = 100.0f;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxHp = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float HpBarHeight = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SMComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HpBar = nullptr;

	UC_HealthBar* HpBarWidget = nullptr;
};
