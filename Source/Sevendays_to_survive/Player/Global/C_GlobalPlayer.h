// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player/Global/DataTable/C_PlayerDataTable.h" // 데이터 테이블
#include "Net/UnrealNetwork.h" // 서버 네트워크
#include "Player/Global/C_PlayerEnum.h"
#include "C_GlobalPlayer.generated.h"


USTRUCT()
struct FireInfo
{
	GENERATED_BODY()
public:
	FVector Start = FVector::ZeroVector;
	FVector End = FVector::ZeroVector;
	FRotator BulletRotation = FRotator::ZeroRotator;
	TSubclassOf<AActor> BulletActor = nullptr;
	float Time = 3.0f;
	//float BulletSpeed = 10000.0f;
};

USTRUCT()
struct Frebound
{
	GENERATED_BODY()
public:
	float PitchMin = -1.0f;
	float PitchMax = 0.5f;
	float YawMin = -1.0f;
	float YawMax = 1.0f;
};

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
class AC_EquipWeapon;
class AC_MainPlayerController;
class UTextRenderComponent;
class UNiagaraComponent; // 이펙트 == 나이아가라
class UNiagaraSystem;
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
	FORCEINLINE UCameraComponent* GetCamera() const { return Cameras; }

	FORCEINLINE TArray<UStaticMeshComponent*> GetStaticItemMesh() const
	{
		return StaticItemMeshs;
	}

	FORCEINLINE TArray<USkeletalMeshComponent*> GetSkeletalItemMesh() const
	{
		return SkeletalItemMeshes;
	}

	FORCEINLINE TMap<EStaticItemSlot, USoundBase*> GetWeaponSounds() const
	{
		return WeaponSounds;
	}

	FORCEINLINE bool GetAImZoomCpp()
	{
		return IsAimCpp;
	}

	FORCEINLINE bool GetRunCpp()
	{
		return IsRunCpp;
	}

	FORCEINLINE bool GetFireCpp()
	{
		return IsFireCpp;
	}

	FORCEINLINE float GetPitchCPP()
	{
		return PitchCPP;
	}

	FORCEINLINE bool GetIsPlayerDieCpp()
	{
		return IsPlayerDieCpp;
	}

	//------------------------------------------------

	EWeaponUseState GetPlayerCurState()
	{
		return PlayerCurState;
	}
	
	void SetPlayerCurState(EWeaponUseState _PlayerCurState)
	{
		PlayerCurState = _PlayerCurState;
	}

	UFUNCTION(BlueprintCallable)
	void Playerhit(int _Damage);

	UFUNCTION()
	void ResetHit();

	UFUNCTION(BlueprintCallable)
	void AttCalstamina();

	UFUNCTION(BlueprintCallable,Reliable, NetMulticast)
	void WeaponSwingSound(FHitResult _Hit, const bool _IsZombie);
	void WeaponSwingSound_Implementation(FHitResult _Hit, const bool _IsZombie);

	UFUNCTION(Reliable, NetMulticast)
	void CreateZombieBlood(FHitResult _Hit);
	void CreateZombieBlood_Implementation(FHitResult _Hit);

	UFUNCTION()
	void Resetmagazinecapacity();

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; // 리플리케이트를 설정하기 위한 함수 필수!
	// Called when the game starts or when spawned
	void BeginPlay() override;
	// Called every frame
	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // 입력 바인드 함수 관리

	// 네트워크 동기화 용 함수
	// (1) 달리기 함수
	UFUNCTION(Reliable, NetMulticast)
	void ChangeSlotMesh(EStaticItemSlot _Slot, UStaticMesh* _Mesh);
	void ChangeSlotMesh_Implementation(EStaticItemSlot _Slot, UStaticMesh* _Mesh);

	UFUNCTION(BlueprintCallable,Reliable, Server)
	void ChangeSlotMeshServer(EStaticItemSlot _Slot, UStaticMesh* _Mesh);
	void ChangeSlotMeshServer_Implementation(EStaticItemSlot _Slot, UStaticMesh* _Mesh);

	UFUNCTION(Reliable, NetMulticast)
	void ChangeSlotSkeletal(ESkerItemSlot _Slot);
	void ChangeSlotSkeletal_Implementation(ESkerItemSlot _Slot);

	UFUNCTION(BlueprintCallable, Reliable, Server)
	void ChangeSlotSkeletalServer(ESkerItemSlot _Slot);
	void ChangeSlotSkeletalServer_Implementation(ESkerItemSlot _Slot);

	UFUNCTION(Reliable, NetMulticast)
	void ChangeNoWeapon();
	void ChangeNoWeapon_Implementation();

	UFUNCTION(BlueprintCallable, Reliable, Server)
	void ChangeNoWeaponServer();
	void ChangeNoWeaponServer_Implementation();

	//UFUNCTION(Reliable, NetMulticast)
	//void ChangeWeaponRifle();

	UFUNCTION(Reliable, Server)
	void FireStart(const FInputActionValue& Value); //
	void FireStart_Implementation(const FInputActionValue& Value);

	UFUNCTION(Reliable, Server)
	void FireEnd(const FInputActionValue& Value); //
	void FireEnd_Implementation(const FInputActionValue& Value);


	UFUNCTION(Reliable, Server)
	void RunStart(const FInputActionValue& Value); //
	void RunStart_Implementation(const FInputActionValue& Value);

	UFUNCTION(Reliable, Server)
	void AimStart(const FInputActionValue& Value); //
	void AimStart_Implementation(const FInputActionValue& Value);

	UFUNCTION(Reliable, Server)
	void RunEnd(const FInputActionValue& Value);
	void RunEnd_Implementation(const FInputActionValue& Value);

	


	UFUNCTION(Reliable, Server)
	void AimEnd(const FInputActionValue& Value); //
	void AimEnd_Implementation(const FInputActionValue& Value);

	UFUNCTION(Reliable, Server)
	void ResultPitchCal(float _Pitch);
	void ResultPitchCal_Implementation(float _Pitch);

	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void JumpCal(const FInputActionValue& Value);

	UFUNCTION(Reliable, NetMulticast)
	void GunLineTrace();
	void GunLineTrace_Implementation();

	UFUNCTION(Reliable, NetMulticast)
	void ShotGunLineTrace();
	void ShotGunLineTrace_Implementation();

	UFUNCTION(Reliable, Server)
	void FireLoop();
	void FireLoop_Implementation();

	UFUNCTION(Reliable, NetMulticast)
	void CreateBulletHole(FHitResult _Hit);
	void CreateBulletHole_Implementation(FHitResult _Hit);


	UFUNCTION()
	void Calstamina();


	UFUNCTION(BlueprintCallable)
	void CrouchCpp(const FInputActionValue& Value);


	UFUNCTION()
	void SpawnBulletMove(float _DeltaTime);

	UFUNCTION(Reliable, Server)
	void ReloadServer();
	void ReloadServer_Implementation();

	UFUNCTION(Reliable, NetMulticast)
	void Reload();
	void Reload_Implementation();

	UFUNCTION(BlueprintCallable,Reliable, Server)
	void MeshInit(EPlayerMesh _Mesh);
	void MeshInit_Implementation(EPlayerMesh _Mesh);

	UFUNCTION()
	void Rebound();



	UC_GlobalAnimInstance* GlobalAnim = nullptr;
	UPROPERTY()
	UC_InputActionDatas* InputData=nullptr;

	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsPlayerDieCpp = false;
private:
	UFUNCTION()
	void PlayerMeshOption();

	UFUNCTION(Reliable, Server)
	void PlayerDieCheck();
	void PlayerDieCheck_Implementation();

	UFUNCTION(Reliable, Server)
	void PlayerReStartCheck();
	void PlayerReStartCheck_Implementation();

	UFUNCTION(Reliable, Server)
	void PlayerTokenCheck(int _Token);
	void PlayerTokenCheck_Implementation(int _Token);

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EWeaponUseState, TSubclassOf<AActor>> GunWeapon;

	// 게임 인스턴스 관리
	FC_PlayerCommonValue PlayerDT;
	FC_CameraValue CameraDT;
	FC_BulletValue BulletDT;
	FC_meleeweaponSound AttWeaponSound;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Cameras = nullptr;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* NameText = nullptr;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> StaticItemMeshs;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<ESkerItemSlot, int> magazinecapacity;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<ESkerItemSlot, UAnimMontage*> ReloadMontages;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EStaticItemSlot, USoundBase*> WeaponSounds;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<USkeletalMeshComponent*> SkeletalItemMeshes;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext = nullptr;

	
	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsRunCpp = false;

	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsAimCpp = false;

	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsFireCpp = false;

	UPROPERTY()
	FTimerHandle timer;

	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsHitCpp = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int Maxstamina = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int stamina = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int staminaCalValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int staminaAttCalValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int staminaJumpCalValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int Hp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float CameraRotSpeed = 100.0f;

	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float PitchCPP = 0.0f;

	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxCalPitchCPP = 30.0f;

	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MinCalPithchCPP = -30.0f;

	UPROPERTY()
	float LineTraceRange = 0.0f;

	UPROPERTY()
	float LineTraceDamage = 0.0f;

	UPROPERTY()
	float PistolAtt = 0.0f;

	UPROPERTY()
	float ShotGunAtt = 0.0f;

	UPROPERTY()
	float RifleAtt = 0.0f;


	UPROPERTY()
	float PistolRange = 0.0f;

	UPROPERTY()
	float ShotGunRange = 0.0f;

	UPROPERTY()
	float RifleRange = 0.0f;

	UPROPERTY()
	int Maxmagazinecapacity=0;

	UPROPERTY()
	int Pistolmagazinecapacity = 0;

	UPROPERTY()
	int ShotGunmagazinecapacity = 0;

	UPROPERTY()
	int Riflemagazinecapacity = 0;

	UPROPERTY()
	float Spreed = 500.0f;

	UPROPERTY()
	float RifleTime = 0.0f;

	UPROPERTY()
	float PistolTIme = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	AC_MainPlayerController* PlayerController = nullptr;

	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EWeaponUseState PlayerCurState = EWeaponUseState::NoWeapon;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AC_EquipWeapon* CurWeapon = nullptr;


	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* hitMontage = nullptr;

	UPROPERTY()
	FRandomStream Random;

	UPROPERTY()
	UMaterialInterface* BulletHoleEffect = nullptr;

	UPROPERTY()
	UNiagaraSystem* ZombieHitEffect = nullptr;

	UPROPERTY()
	UNiagaraSystem* thisHitBlood = nullptr;

	UPROPERTY()
	TArray<FireInfo> BulletInfos;

	UPROPERTY(Category = "Contents", Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int PlayerSpawnCheckToken = -1;

	UPROPERTY(Category = "Contents", Replicated, EditAnywhere, BlueprintReadOnly,  meta = (AllowPrivateAccess = "true"))
	EPlayerMesh characterResultMesh = EPlayerMesh::Player1;


	UPROPERTY()
	FVector ReStartLocation = FVector::ZeroVector;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* MontageDiePlay=nullptr;
};
