// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_GlobalPlayer.generated.h"

class UC_STSInstance; // �ν��Ͻ�
class USpringArmComponent; // ������ ��
class UCameraComponent; // ī�޶� ������Ʈ
class UInputMappingContext; // �Է� ����
class UInputAction; // �Է� �׼�

struct FInputActionValue; // 

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_GlobalPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_GlobalPlayer();

	
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return SpringArm; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return Camera; }

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;
	// Called every frame
	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for movement input */
	virtual void Move(const FInputActionValue& Value);

	/** Called for looking input */
	virtual void Look(const FInputActionValue& Value);

	virtual void IdleStart();
	virtual void MoveStart();
	virtual void JumpStart();

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction = nullptr;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction = nullptr;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction = nullptr;

private:
	UC_STSInstance* STSInstance = nullptr;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera = nullptr;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext = nullptr;

};
