// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Global/C_GlobalPlayer.h"
#include "Player/Global/C_PlayerEnum.h"
#include "C_NickMainPlayer.generated.h"

//class UC_GlobalAnimInstance;
/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_NickMainPlayer : public AC_GlobalPlayer
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;
	// Called every frame
	void Tick(float DeltaTime) override;

	// �Է� �ݹ� ó��
	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// �ൿ
	void Move(const FInputActionValue& Value) override;
	void Look(const FInputActionValue & Value) override;

	// �ִϸ��̼�
	void IdleStart() override;
	void MoveStart() override;
	void JumpStart() override;
private:
	//UC_GlobalAnimInstance* GlobalAnim = nullptr;

	//UPROPERTY(Replicated, Server)
	EPlayerState  Ani = EPlayerState::None;
	
};
