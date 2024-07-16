// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map/C_MapActor.h"
#include "Components/WidgetComponent.h"
#include "C_MapDamageTaker.generated.h"

class UC_HealthBar;

UCLASS(Abstract)
class SEVENDAYS_TO_SURVIVE_API AC_MapDamageTaker : public AC_MapActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_MapDamageTaker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void UpdateHpBar();

	UFUNCTION(BlueprintCallable)
	void HideHpBar();

	UFUNCTION(BlueprintCallable)
	void SetMaxHp(int _MaxHp);

protected:
	UFUNCTION(NetMulticast, Reliable)
	void ReceiveDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	void ReceiveDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	virtual void PreDestroy() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SMComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HpBar = nullptr;

	UC_HealthBar* HpBarWidget = nullptr;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Hp = 100.0f;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxHp = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float HpBarHeight = 100.0f;
};
