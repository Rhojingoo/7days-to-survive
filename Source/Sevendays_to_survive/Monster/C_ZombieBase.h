// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Sound/SoundWave.h"
#include "Perception/AISense_Hearing.h"
#include "C_ZombieBase.generated.h"


UENUM(BlueprintType) // BlueprintType은 이 enum을 블루프린트에서 사용할 수 있게 해줍니다.
enum class MonsterEnum : uint8
{
	None UMETA(DisplayName = "None"),
	Idle UMETA(DisplayName = "Idle"),
	Move UMETA(DisplayName = "Move"),
	Attack UMETA(DisplayName = "Attack"),
	RunAttack UMETA(DisplayName = "RunAttack"),
	Shout UMETA(DisplayName = "Shout"),
	Climb UMETA(DisplayName = "Climb"),
	Dead UMETA(DisplayName = "Dead"),
	Run UMETA(DisplayName = "Run"),
	RangedAttack UMETA(DisplayName = "RangedAttack"),
	Faint UMETA(DisplayName = "Faint"),
	Rush UMETA(DisplayName = "Rush"),
	Jump UMETA(DisplayName = "Jump"),
	End UMETA(DisplayName = "End"),
	Find UMETA(DisplayName = "Find")
};

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_ZombieBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_ZombieBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree* AITree;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Idle();
	virtual void Move(FVector _Location);
	virtual void Run(FVector _Location);
	virtual void Attack();
	virtual void RunAttack();
	virtual void ShoutAttack();
	virtual void MonsterJump();
	void AddLocation(FVector _Location);
	FVector GetComponentLocation();


	UFUNCTION(BlueprintCallable,NetMulticast, Reliable)
	void SetRagDoll();
	void SetRagDoll_Implementation();

	virtual void OnAttackNotifyBegin();
	virtual void OnAttackNotifyEnd();

	UFUNCTION(BlueprintCallable)
	MonsterEnum GetState();

	// ServerOnlyFunction의 유효성 검사 함수
	void SetState(MonsterEnum _Enum);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FString GetName();

	UFUNCTION(BlueprintCallable)
	void Collision(AActor* _Actor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
	class UAudioComponent* AudioComponent;

	virtual void SetName(FString _Name) PURE_VIRTUAL(AC_ZombieBase::SetName, ;);

	bool IsShout() { return Shout; }

	bool BottomRayTrace();
	bool MiddleRayTrace();

	void SetMCP(class UC_MonsterComponent* _MCP) {
		MCP = _MCP;
	}

	UFUNCTION(BlueprintCallable)
	void SetHP(double _Damage);

	UFUNCTION(BlueprintCallable)
	double GetDamage() const;

	UFUNCTION(NetMulticast, Reliable)
	void PlayFindSound();
	void PlayFindSound_Implementation();


	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void ForceFindTargetActor(AActor* _Actor);

protected:
	FString MonsterName;
	float LayLength = 100.f;

	class UC_MonsterAnim* AnimInstance;

	UPROPERTY(Replicated, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	MonsterEnum MonsterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
	class UBoxComponent* AttackComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
	bool Shout = false;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void Make_Noise(float _Loudness);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* BottomArrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* MiddleArrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* LocationComponent;

	UPROPERTY()
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY()
	UC_MonsterComponent* MCP = nullptr;

	UFUNCTION(NetMulticast, Reliable)
	void PlayDeadSound(USkeletalMeshComponent* _Mesh);
	void PlayDeadSound_Implementation(USkeletalMeshComponent* _Mesh);

};


