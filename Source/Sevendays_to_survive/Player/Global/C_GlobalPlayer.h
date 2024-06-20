// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_GlobalPlayer.generated.h"

struct FC_PlayerDataTable; // 인스턴스
class USpringArmComponent; // 스프링 암
class UCameraComponent; // 카메라 컴포넌트
class UInputMappingContext; // 입력 매핑
class UInputAction; // 입력 액션
class UC_GlobalAnimInstance;
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

	// 행동
	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);

	// 애니메이션 스타트 가상 함수
	virtual void IdleStart();
	virtual void MoveStart();
	virtual void JumpStart();


	// 액션 키 정리
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction = nullptr;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction = nullptr;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction = nullptr;

	// 애님 인스턴스 관리
	UC_GlobalAnimInstance* GlobalAnim = nullptr;
private:
	// 게임 인스턴스 관리
	FC_PlayerDataTable* PlayerDT = nullptr;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera = nullptr;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext = nullptr;

};
