// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_ZombieBase.h"
#include "Net/UnrealNetwork.h"
#include "C_MonsterAnim.h"
#include "MonsterData/MonsterDataRow.h"
#include "STS/C_STSInstance.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"



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
	UAnimInstance* Anim = Sk->GetAnimInstance();	//c_zombiebase 기반 c++ 좀비를 하나 만들어서, 그 기반 블프까지 animation instance
	AnimInstance = Cast<UC_MonsterAnim>(Anim);

	if (nullptr == AnimInstance) {
		UE_LOG(LogTemp, Fatal, TEXT("Not Setting Animation Instance"));
	}
	if (HasAuthority())
	{
		// 서버에서만 초기 상태 설정
		MonsterState = MonsterEnum::Idle;
	}

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


	//if (MonsterState == MonsterEnum::Attack || MonsterState == MonsterEnum::RunAttack)
	//{
	//	AnimInstance->ChangeAnimation(MonsterState);
	//}
	//TMap<uint8, class UAnimMontage* > AnimMontages = AnimInstance->GetAnimMontages();

	//UAnimMontage* PrevMon = AnimInstance->GetCurrentActiveMontage();
	//AnimInstance->ChangeAnimation(MonsterState);
}

// Called to bind functionality to input
void AC_ZombieBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AC_ZombieBase::SetRagDoll() 
{
	UCharacterMovementComponent* Component = GetCharacterMovement();
	Component->DisableMovement();

	// Enable physics simulation on the skeletal mesh
	USkeletalMeshComponent* MyMesh = GetMesh();
	if (MyMesh)
	{
		MyMesh->SetSimulatePhysics(true);
		MyMesh->SetCollisionProfileName(TEXT("Ragdoll"));

		// Optionally disable animation
		MyMesh->bPauseAnims = true;

		UCapsuleComponent* Capsule = GetCapsuleComponent();
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MyMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		// Set the root component to follow the ragdoll
		AC_MonsterAIBase* ActorController = Cast<AC_MonsterAIBase>(GetController());
		if (ActorController->IsValidLowLevel())
		{
			ActorController->UnPossess();
			ActorController->Destroy();
		}
	}
}

void AC_ZombieBase::Idle()
{
	SetState(MonsterEnum::Idle);
}

void AC_ZombieBase::Move(FVector _Location)
{
	SetState(MonsterEnum::Move);
	AddMovementInput(_Location);
}

void AC_ZombieBase::Run(FVector _Location)
{
	SetState(MonsterEnum::Run);
	AddMovementInput(_Location);
}

void AC_ZombieBase::Attack()
{
	SetState(MonsterEnum::Attack);
}

void AC_ZombieBase::RunAttack()
{
	SetState(MonsterEnum::RunAttack);
}

void AC_ZombieBase::OnNotifyBegin()
{
	AttackComponent->SetCollisionProfileName("OverlapAllDynamic");
}

void AC_ZombieBase::OnNotifyEnd()
{
	AttackComponent->SetCollisionProfileName("NoCollision");
}

MonsterEnum AC_ZombieBase::GetState()
{
	return MonsterState;
}

void AC_ZombieBase::SetState(MonsterEnum _Enum)
{
	if (MonsterState != _Enum) {
		MonsterState = _Enum;
	}
}

void AC_ZombieBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AC_ZombieBase, MonsterState);
}

FString AC_ZombieBase::GetName()
{
	return MonsterName;
}

void AC_ZombieBase::Collision(AActor* _Actor)
{
	// if _Actor is Player
}

