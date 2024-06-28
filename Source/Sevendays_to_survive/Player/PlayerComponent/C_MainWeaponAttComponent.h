// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_MainWeaponAttComponent.generated.h"

class AC_GlobalPlayer;

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SEVENDAYS_TO_SURVIVE_API UC_MainWeaponAttComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_MainWeaponAttComponent();

	UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
	void AttStart(); //
	void AttStart_Implementation();

	UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
	void AttStart2(); //
	void AttStart2_Implementation();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:	
	// Called every frame
	// Called every frame
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AC_GlobalPlayer* Player;
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* PlayerMesh;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttAni;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttAni2;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsAttCPP = false;
};
