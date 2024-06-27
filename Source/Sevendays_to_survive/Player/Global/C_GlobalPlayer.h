// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player/Global/DataTable/C_PlayerDataTable.h" // 데이터 테이블
#include "Net/UnrealNetwork.h" // 서버 네트워크
#include "Player/Global/C_PlayerEnum.h"
#include "C_GlobalPlayer.generated.h"

class USpringArmComponent; // 스프링 암
class UCameraComponent; // 카메라 컴포넌트
class UInputMappingContext; // 입력 매핑
class UInputAction; // 입력 액션
class UC_GlobalAnimInstance; // 애님 인스턴스
class UStaticMeshComponent;
class UChildActorComponent;
class UC_InventoryComponent;
class UC_BuildingComponent;
class UC_MapInteractionComponent;
class UC_InputActionDatas;
struct FInputActionValue; // 입력 값

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_GlobalPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_GlobalPlayer();

	
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; } // 총 저장 용 매쉬
	/** Returns FirstPersonCameraComponent subobject **/

	UFUNCTION(BlueprintCallable)
	void ChangeSlotMesh(EPlayerItemSlot _Slot, UStaticMesh* _Mesh);

	// 총 관련 bool 함수
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();
	//------------------------------------------------

	// 네트워크 동기화 용 함수
	// (1) 달리기 함수
	UFUNCTION(Reliable, Server)
	void RunStart(const FInputActionValue& Value); //
	void RunStart_Implementation(const FInputActionValue& Value);
	UFUNCTION(Reliable, Server)
	void RunEnd(const FInputActionValue& Value);
	void RunEnd_Implementation(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void Calstamina();

	UFUNCTION(BlueprintCallable)
	void CrouchCpp(const FInputActionValue& Value);

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; // 리플리케이트를 설정하기 위한 함수 필수!
	// Called when the game starts or when spawned
	void BeginPlay() override;
	// Called every frame
	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // 입력 바인드 함수 관리


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;


	UC_GlobalAnimInstance* GlobalAnim = nullptr;
	UPROPERTY()
	UC_InputActionDatas* InputData=nullptr;

private:
	// 게임 인스턴스 관리
	FC_PlayerCommonValue PlayerDT;
	FC_CameraValue CameraDT;
	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera = nullptr;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* TPSZoomSpringArm = nullptr;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* TPSZoomCamera = nullptr;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* FPSSpringArm = nullptr;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* FPSCamera = nullptr;
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> ItemMesh;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float CameraRotSpeed = 100.0f;

	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsRunCpp = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int Maxstamina = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int stamina = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int staminaCalValue = 0;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float Hp = 0.0f;
};
