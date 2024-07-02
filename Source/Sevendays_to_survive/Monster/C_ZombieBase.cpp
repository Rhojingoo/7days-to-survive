// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_ZombieBase.h"
#include "Net/UnrealNetwork.h"
#include "C_MonsterAnim.h"
#include "MonsterData/MonsterDataRow.h"
#include "STS/C_STSInstance.h"
#include "Components/BoxComponent.h"

// Sets default values
AC_ZombieBase::AC_ZombieBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	AttackComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	AttackComponent->SetupAttachment(GetMesh());
	AttackComponent->SetCollisionProfileName("NoCollision");

}

// Called when the game starts or when spawned
void AC_ZombieBase::BeginPlay()
{
	Super::BeginPlay();
	USkeletalMeshComponent* Sk = GetMesh();
	UAnimInstance* Anim = Sk->GetAnimInstance();
	AnimInstance = Cast<UC_MonsterAnim>(Anim);
	MonsterState = MonsterEnum::Idle;

	UC_STSInstance* Inst = Cast<UC_STSInstance>(GetGameInstance());
	FMonsterDataRow* Row = Inst->GetMonsterData(*MonsterName);

	{
		for (TPair<uint8, class UAnimMontage*> Montage : Row->AnimMontages)
		{
			AnimInstance->PushAnimation(Montage.Key, Montage.Value);
		}
	}
}

// Called every frame
void AC_ZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//TMap<uint8, class UAnimMontage* > AnimMontages = AnimInstance->GetAnimMontages();

	//UAnimMontage* PrevMon = AnimInstance->GetCurrentActiveMontage();
	//AnimInstance->ChangeAnimation(MonsterState);
}

// Called to bind functionality to input
void AC_ZombieBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AC_ZombieBase::Idle()
{
	SetState_Implementation(MonsterEnum::Idle);
}

void AC_ZombieBase::Move(FVector _Location)
{
	AddMovementInput(_Location);
	SetState_Implementation(MonsterEnum::Move);
}

void AC_ZombieBase::Attack()
{
	//AnimInstance->ChangeAnimation(MonsterEnum::Attack);
	SetState_Implementation(MonsterEnum::Attack);
}

void AC_ZombieBase::RunAttack()
{
	SetState_Implementation(MonsterEnum::RunAttack);
}

void AC_ZombieBase::CollisionOn()
{
	AttackComponent->SetCollisionProfileName("OverlapAllDynamic");
}

void AC_ZombieBase::CollisionOff()
{
	AttackComponent->SetCollisionProfileName("NoCollision");
}

MonsterEnum AC_ZombieBase::GetState()
{
	return MonsterState;
}

bool AC_ZombieBase::SetState_Validate(MonsterEnum _Enum)
{
	return true;
}

void AC_ZombieBase::SetState_Implementation(MonsterEnum _Enum)
{
	MonsterState = _Enum;
}

void AC_ZombieBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AC_ZombieBase, MonsterState);
}

//void AC_ZombieBase::GetDataFromName()
//{
//}

FString AC_ZombieBase::GetName()
{
	return MonsterName;
}

void AC_ZombieBase::Collision(AActor* _Actor)
{
	// if _Actor is Player
}

