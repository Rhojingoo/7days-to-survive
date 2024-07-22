// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_ZombieBase.h"
#include "Net/UnrealNetwork.h"
#include "C_MonsterAnim.h"
#include "MonsterData/MonsterDataRow.h"
#include "STS/C_STSInstance.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Map/C_MapActor.h"
#include "..\Monster\Component\C_MonsterComponent.h"


// Sets default values
AC_ZombieBase::AC_ZombieBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bAutoActivate = false;

	AttackComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	AttackComponent->SetupAttachment(GetMesh());
	AttackComponent->SetCollisionProfileName("NoCollision");

	BottomArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("BottomArrowComponent"));
	BottomArrowComponent->SetupAttachment(RootComponent); // RootComponent에 부착

	MiddleArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MiddleArrowComponent"));
	MiddleArrowComponent->SetupAttachment(RootComponent); // RootComponent에 부착

	LocationComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("LocationComponent"));
	LocationComponent->SetupAttachment(RootComponent); // RootComponent에 부착

	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
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

	if (HasAuthority())
	{
		AnimInstance->ChangeAnimation(MonsterEnum::Idle);
		Inst->AddZombieArray(this);
	}
}
// Called every frame
void AC_ZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//RayTrace();
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

void AC_ZombieBase::SetRagDoll_Implementation()
{

	UCharacterMovementComponent* Component = GetCharacterMovement();
	Component->DisableMovement();

	// Enable physics simulation on the skeletal mesh
	USkeletalMeshComponent* MyMesh = GetMesh();
	if (MyMesh)
	{
		UC_STSInstance* Inst = Cast<UC_STSInstance>(GetGameInstance());
		Inst->RemoveZombieArray(this);
		MyMesh->SetSimulatePhysics(true);
		MyMesh->SetCollisionProfileName(TEXT("Ragdoll"));

		// Optionally disable animation
		MyMesh->bPauseAnims = true;

		PlayDeadSound(MyMesh);

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
		FTimerHandle ZombieDestory;

		GetWorld()->GetTimerManager().SetTimer(ZombieDestory, FTimerDelegate::CreateLambda([&]()
			{
				this->Destroy();
			}), 5.0f, false);
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
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void AC_ZombieBase::Run(FVector _Location)
{
	SetState(MonsterEnum::Run);
	AddMovementInput(_Location);
	GetCharacterMovement()->MaxWalkSpeed = 700.f;
}

void AC_ZombieBase::Attack()
{
	SetState(MonsterEnum::Attack);
}

void AC_ZombieBase::ShoutAttack()
{
	SetState(MonsterEnum::Shout);
}

void AC_ZombieBase::MonsterJump()
{
	SetState(MonsterEnum::Jump);
	Jump();
}

void AC_ZombieBase::AddLocation(FVector _Location)
{
	AddMovementInput(_Location);
}

FVector AC_ZombieBase::GetComponentLocation()
{
	FVector Location = LocationComponent->GetComponentLocation();
	return Location;
}

void AC_ZombieBase::RunAttack()
{
	SetState(MonsterEnum::RunAttack);
}

void AC_ZombieBase::OnAttackNotifyBegin()
{
	AttackComponent->SetCollisionProfileName("OverlapAllDynamic");
}

void AC_ZombieBase::OnAttackNotifyEnd()
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


void AC_ZombieBase::Make_Noise(float _Loudness)
{
	UAISense_Hearing::ReportNoiseEvent(this, GetActorLocation(), _Loudness, this, 0.0f, TEXT("Noise"));
}

bool AC_ZombieBase::BottomRayTrace()
{
	bool MiddleIsHit = false;
	bool bottomIsHit = false;



	{
		FVector Start = BottomArrowComponent->GetComponentLocation();  // 레이의 시작점: 캐릭터 위치
		FVector ForwardVector = GetActorForwardVector();  // 캐릭터의 전방 벡터
		FVector End = ((ForwardVector * LayLength) + Start);  // 레이의 끝점: 전방 1000 유닛
		FHitResult HitResult;

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);  // 충돌 검사에서 현재 캐릭터 무시

		ETraceTypeQuery::TraceTypeQuery1;
		bottomIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
		//bool bHit = UKismetSystemLibrary::LineTraceSingleForObjects(
		//	GetWorld(),
		//	Start,
		//	End,
		//	ObjectTypes,
		//	false, // 복합 콜리전 여부
		//	TArray<AActor*>(), // 무시할 액터들
		//	EDrawDebugTrace::ForDuration, // 디버깅을 위한 트레이스
		//	HitResult,
		//	true // 트레이스를 시각화할지 여부
		//);

		// 디버그 라인 그리기
#ifdef WITH_DEITOR
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
#endif // WITH_DEITOR
		if (bottomIsHit && nullptr != HitResult.GetActor())
		{
			AC_MapActor* MapActor = Cast<AC_MapActor>(HitResult.GetActor());
			if (MapActor->IsValidLowLevel() == true) {
				bottomIsHit = true;
			}
			else {
				bottomIsHit = false;
			}
		}
		else {
			bottomIsHit = false;
		}


	}


	{
		FVector Start = MiddleArrowComponent->GetComponentLocation();  // 레이의 시작점: 캐릭터 위치
		FVector ForwardVector = GetActorForwardVector();  // 캐릭터의 전방 벡터
		FVector End = ((ForwardVector * LayLength) + Start);  // 레이의 끝점: 전방 1000 유닛
		FHitResult HitResult;

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);  // 충돌 검사에서 현재 캐릭터 무시

		ETraceTypeQuery::TraceTypeQuery1;
		MiddleIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
		//bool bHit = UKismetSystemLibrary::LineTraceSingleForObjects(
		//	GetWorld(),
		//	Start,
		//	End,
		//	ObjectTypes,
		//	false, // 복합 콜리전 여부
		//	TArray<AActor*>(), // 무시할 액터들
		//	EDrawDebugTrace::ForDuration, // 디버깅을 위한 트레이스
		//	HitResult,
		//	true // 트레이스를 시각화할지 여부
		//);

		// 디버그 라인 그리기
#ifdef WITH_DEITOR
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
#endif // WITH_DEITOR
		if (MiddleIsHit && nullptr != HitResult.GetActor())
		{
			AC_MapActor* MapActor = Cast<AC_MapActor>(HitResult.GetActor());
			if (MapActor->IsValidLowLevel() == true) {
				MiddleIsHit = true;
			}
			else {
				MiddleIsHit = false;
			}
		}
		else {
			MiddleIsHit = false;
		}
	}

	if (false == MiddleIsHit && true == bottomIsHit) {  //바텀만 맞아야 true
		return true;
	}
	else {
		return false;
	}
}

bool AC_ZombieBase::MiddleRayTrace()
{
	bool MiddleIsHit = false;
	bool bottomIsHit = false;
	{
		FVector Start = BottomArrowComponent->GetComponentLocation();  // 레이의 시작점: 캐릭터 위치
		FVector ForwardVector = GetActorForwardVector();  // 캐릭터의 전방 벡터
		FVector End = ((ForwardVector * LayLength) + Start);  // 레이의 끝점: 전방 1000 유닛
		FHitResult HitResult;

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);  // 충돌 검사에서 현재 캐릭터 무시

		ETraceTypeQuery::TraceTypeQuery1;
		bottomIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
		//bool bHit = UKismetSystemLibrary::LineTraceSingleForObjects(
		//	GetWorld(),
		//	Start,
		//	End,
		//	ObjectTypes,
		//	false, // 복합 콜리전 여부
		//	TArray<AActor*>(), // 무시할 액터들
		//	EDrawDebugTrace::ForDuration, // 디버깅을 위한 트레이스
		//	HitResult,
		//	true // 트레이스를 시각화할지 여부
		//);

		// 디버그 라인 그리기
#ifdef WITH_DEITOR
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
#endif // WITH_DEITOR
		if (bottomIsHit && nullptr != HitResult.GetActor())
		{
			AC_MapActor* MapActor = Cast<AC_MapActor>(HitResult.GetActor());
			if (MapActor->IsValidLowLevel() == true) {
				bottomIsHit = true;
			}
			else {
				bottomIsHit = false;
			}
		}
		else {
			bottomIsHit = false;
		}


	}


	{
		FVector Start = MiddleArrowComponent->GetComponentLocation();  // 레이의 시작점: 캐릭터 위치
		FVector ForwardVector = GetActorForwardVector();  // 캐릭터의 전방 벡터
		FVector End = ((ForwardVector * LayLength) + Start);  // 레이의 끝점: 전방 1000 유닛
		FHitResult HitResult;

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);  // 충돌 검사에서 현재 캐릭터 무시

		ETraceTypeQuery::TraceTypeQuery1;
		MiddleIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
		//bool bHit = UKismetSystemLibrary::LineTraceSingleForObjects(
		//	GetWorld(),
		//	Start,
		//	End,
		//	ObjectTypes,
		//	false, // 복합 콜리전 여부
		//	TArray<AActor*>(), // 무시할 액터들
		//	EDrawDebugTrace::ForDuration, // 디버깅을 위한 트레이스
		//	HitResult,
		//	true // 트레이스를 시각화할지 여부
		//);

		// 디버그 라인 그리기
#ifdef WITH_DEITOR
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
#endif // WITH_DEITOR
		if (MiddleIsHit && nullptr != HitResult.GetActor())
		{
			AC_MapActor* MapActor = Cast<AC_MapActor>(HitResult.GetActor());
			if (MapActor->IsValidLowLevel() == true) {
				MiddleIsHit = true;
			}
			else {
				MiddleIsHit = false;
			}
		}
		else {
			MiddleIsHit = false;
		}
	}

	if (true == MiddleIsHit && true == bottomIsHit) {  //바텀만 맞아야 true
		return true;
	}
	else {
		return false;
	}
}

void AC_ZombieBase::SetHP(double _Damage)
{
	if(true == HasAuthority()){
		double* HP = MCP->GetData()->GetHPRef();
		*HP -= _Damage;
		if (*HP <= 0) {
			SetRagDoll();
		}
	}
}

double AC_ZombieBase::GetDamage() const {
	if (true == HasAuthority()) {
		return MCP->GetData()->GetAtt();
	}
	return 0.0f;
}

void AC_ZombieBase::PlayDeadSound_Implementation(USkeletalMeshComponent* _Mesh)
{
	UC_STSInstance* Inst = Cast<UC_STSInstance>(GetGameInstance());
	FMonsterDataRow* Row = Inst->GetMonsterData(*MonsterName);
	if (nullptr != Row)
	{
		USoundWave** SoundWavePtr = Row->SoundFile.Find(7);
		if (nullptr != SoundWavePtr)
		{
			UGameplayStatics::PlaySoundAtLocation(_Mesh->GetWorld(), *SoundWavePtr, _Mesh->GetComponentLocation());
		}
	}
}

void AC_ZombieBase::PlayFindSound_Implementation()
{
	UC_STSInstance* Inst = Cast<UC_STSInstance>(GetGameInstance());
	FMonsterDataRow* Row = Inst->GetMonsterData(*MonsterName);
	if (nullptr != Row)
	{
		USoundWave** SoundWavePtr = Row->SoundFile.Find(14);
		if (nullptr != SoundWavePtr)
		{
			AudioComponent->SetSound(*SoundWavePtr);
			AudioComponent->Play();
		}
	}
}

void AC_ZombieBase::ForceFindTargetActor(AActor* _Actor)
{
	AC_MonsterAIBase* AIController = Cast<AC_MonsterAIBase>(GetController());
	if (AIController != nullptr) {
		AIController->SetTargetActor(_Actor);
	}
}
