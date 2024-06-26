// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_PunchAttComponent.generated.h"

class AC_NickMainPlayer;
class UAnimMontage;

UCLASS(Blueprintable,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SEVENDAYS_TO_SURVIVE_API UC_PunchAttComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_PunchAttComponent();

	UFUNCTION(BlueprintCallable,Reliable, NetMulticast)
	void AttStart(); //
	void AttStart_Implementation();

	void ReSetComboAtt();
	void SetAttCombo();
	void SetAttCombo2();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:	
	// Called every frame
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AC_NickMainPlayer* Player;
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* PlayerMesh;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsAttCPP = false;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int ComboCPP = 0;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> AttAni;

	FScriptDelegate Delegate_OnMontageNotifyBegin;
};
