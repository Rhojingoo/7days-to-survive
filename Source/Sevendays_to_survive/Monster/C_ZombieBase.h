// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	End UMETA(DisplayName = "End")
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
	UFUNCTION(BlueprintCallable)
	void SetRagDoll();

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

	virtual void SetName(FString _Name) PURE_VIRTUAL(AC_ZombieBase::SetName, ;);

protected:
	FString MonsterName;

	class UC_MonsterAnim* AnimInstance;

	UPROPERTY(Replicated, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	MonsterEnum MonsterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
	class UBoxComponent* AttackComponent;
};


