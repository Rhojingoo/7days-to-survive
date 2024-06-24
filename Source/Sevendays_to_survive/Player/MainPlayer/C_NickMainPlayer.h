// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Global/C_GlobalPlayer.h"
#include "C_NickMainPlayer.generated.h"

class UAnimMontage;
//class UC_GlobalAnimInstance;
/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_NickMainPlayer : public AC_GlobalPlayer
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Reliable, Server)
	void PunchAtt(const FInputActionValue& Value);
	void PunchAtt_Implementation(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Reliable, Server)
	void PunchAttEnd(const FInputActionValue& Value);
	void PunchAttEnd_Implementation(const FInputActionValue& Value);
protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; // 리플리케이트를 설정하기 위한 함수 필수!
	// Called when the game starts or when spawned
	void BeginPlay() override;
	// Called every frame
	void Tick(float DeltaTime) override;

	// 입력 콜백 처리
	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* MontageToPlay;
};
