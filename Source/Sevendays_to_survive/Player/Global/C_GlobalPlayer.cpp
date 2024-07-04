// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Global/C_GlobalPlayer.h"
#include "STS/C_STSInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Player/MainController/C_MainPlayerController.h"
#include "Player/Global/C_PlayerEnum.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Player/Input/C_InputActionDatas.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon/Global/DataTable/C_WeaponDataTable.h"
#include "Weapon/C_EquipWeapon.h"
#include "Weapon/C_GunComponent.h"


// Sets default values
AC_GlobalPlayer::AC_GlobalPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerMeshOption();
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	//PlayerDT = STSInstance->GetPlayerDataTable();
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera"));
	SpringArm->SetupAttachment(GetMesh(), *FString("Head"));
	//SpringArm->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	Cameras = CreateDefaultSubobject<UCameraComponent >(TEXT("FollowCamera"));
	Cameras->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	

	//// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	//Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	//Mesh1P->SetOnlyOwnerSee(true);
	//Mesh1P->SetupAttachment(Camera);
	//Mesh1P->bCastDynamicShadow = false;
	//Mesh1P->CastShadow = false;
	////Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	//Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	
	{
		{
			UEnum* Enum = StaticEnum<EStaticItemSlot>();
			// UStaticMeshComponent 슬롯 전용
			for (size_t i = 0; i < static_cast<size_t>(EStaticItemSlot::SlotMax); i++)
			{
				FString Name = Enum->GetNameStringByValue(i);
				UStaticMeshComponent* NewSlotMesh = CreateDefaultSubobject<UStaticMeshComponent>(*Name);
				NewSlotMesh->SetupAttachment(GetMesh(), *Name);
				NewSlotMesh->SetCollisionProfileName(TEXT("NoCollision"));

				StaticItemMesh.Push(NewSlotMesh);
			}
		}
		
		{
			UEnum* Enum = StaticEnum<ESkerItemSlot>();
			// USkeletalMeshComponent 슬롯 전용
			for (size_t i = 0; i < static_cast<size_t>(ESkerItemSlot::SlotMax); i++)
			{
				FString Name = Enum->GetNameStringByValue(i);
				USkeletalMeshComponent* NewSlotMesh = CreateDefaultSubobject<USkeletalMeshComponent>(*Name);
				NewSlotMesh->SetupAttachment(GetMesh(), *Name);
				NewSlotMesh->SetCollisionProfileName(TEXT("NoCollision"));
				SkeletalItemMesh.Push(NewSlotMesh);
			}
		}
	}

	// 데이터 에셋
	{
		FString RefPathString = TEXT("/Script/Sevendays_to_survive.C_InputActionDatas'/Game/Level/TestLevel/CharTest/Player/Input/DA_Input.DA_Input'");

		ConstructorHelpers::FObjectFinder<UC_InputActionDatas> ResPath(*RefPathString);

		// 유효한 리소스냐를 판단할수 있습니다.
		if (false == ResPath.Succeeded())
		{
			return;
		}

		InputData = ResPath.Object;
	}
}

void AC_GlobalPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AC_GlobalPlayer, IsRunCpp);
	DOREPLIFETIME(AC_GlobalPlayer, PlayerCurState);
	DOREPLIFETIME(AC_GlobalPlayer, PitchCPP);
	DOREPLIFETIME(AC_GlobalPlayer, IsAimCpp);
	DOREPLIFETIME(AC_GlobalPlayer, CurWeapon);
	DOREPLIFETIME(AC_GlobalPlayer, IsFireCpp);
}

// Called when the game starts or when spawned
void AC_GlobalPlayer::BeginPlay()
{
	Super::BeginPlay();
	UC_STSInstance* STSInstance = GetWorld()->GetGameInstanceChecked<UC_STSInstance>();
	CameraDT = STSInstance->GetPlayerDataTable()->CameraValue;
	PlayerDT = STSInstance->GetPlayerDataTable()->PlayerValue;
	
	Rifle = STSInstance->GetWeaPonDataTable(FName("M4"))->Equip;

	{
		FString& Port = STSInstance->TitleToGameInfo.ServerPort;
		//if (STSInstance->TitleToGameInfo.ServerOpenCheck == true)
		//{
		//	return;
		//}
		int PortNumber = FCString::Atoi(*Port);
		if (PortNumber == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (PortNumber == 0)"), __FUNCTION__, __LINE__);
			PortNumber = 30002;
			// UE_LOG(GIMATLog, Fatal, TEXT("%S(%u)> if (PortNumber == 0)"), __FUNCTION__, __LINE__);
		}

		// FString:: Inst->SideScrollGameInfo.PORT;
		if (GetLocalRole() == ENetRole::ROLE_Authority)
		{
			STSInstance->EnableListenServer(true, PortNumber);
		}
	}


	// 카메라 데이터 테이블 값 가져오기
	{
		SpringArm->TargetArmLength = CameraDT.TargetArmLength;
		CameraRotSpeed = CameraDT.CameraRotSpeed;
	}

	
	// 플레이어 데이터 테이블 값 가져오기
	{
		GetCharacterMovement()->MaxWalkSpeed = PlayerDT.WalkSpeed;
		GetCharacterMovement()->JumpZVelocity = PlayerDT.JumpZVelocity;
		Maxstamina= PlayerDT.stamina;
		stamina = PlayerDT.stamina;
		staminaCalValue = PlayerDT.staminaCalValue;
		Hp = PlayerDT.Hp;
	}
	
	//Add Input Mapping Context
	PlayerController = Cast<AC_MainPlayerController>(Controller);
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	/*{
		TSubclassOf<AActor> M4= STSInstance->GetWeaPonDataTable(FName("M4"))->Equip;
		AC_EquipWeapon* Gun= GetWorld()->SpawnActor<AC_EquipWeapon>(M4);
		GunWeapon.Add(EWeaponUseState::Rifle, Gun);
	}*/

	//CurWeapon = GetWorld()->SpawnActor<AC_EquipWeapon>(Rifle);
	//CurWeapon->GetWeaponMesh()->AttachWeapon(this);
	//CurWeapon->SetActorHiddenInGame(false);
}

// Called every frame
void AC_GlobalPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Calstamina();
}

// Called to bind functionality to input
void AC_GlobalPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(InputData->Actions[EPlayerState::Jump], ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(InputData->Actions[EPlayerState::Jump], ETriggerEvent::Completed, this, &ACharacter::StopJumping);


		// Moving
		EnhancedInputComponent->BindAction(InputData->Actions[EPlayerState::Move], ETriggerEvent::Triggered, this, &AC_GlobalPlayer::Move);

		// Run
		
		EnhancedInputComponent->BindAction(InputData->Actions[EPlayerState::Run], ETriggerEvent::Triggered, this, &AC_GlobalPlayer::RunStart);
		
		
		EnhancedInputComponent->BindAction(InputData->Actions[EPlayerState::Run], ETriggerEvent::Completed, this, &AC_GlobalPlayer::RunEnd);

		// Looking
		EnhancedInputComponent->BindAction(InputData->Actions[EPlayerState::Look], ETriggerEvent::Triggered, this, &AC_GlobalPlayer::LookMove);

		//Crouch
		EnhancedInputComponent->BindAction(InputData->Actions[EPlayerState::Crouch], ETriggerEvent::Started, this, &AC_GlobalPlayer::CrouchCpp);

		EnhancedInputComponent->BindAction(InputData->Actions[EPlayerState::Zoom], ETriggerEvent::Started, this, &AC_GlobalPlayer::AimStart);
		EnhancedInputComponent->BindAction(InputData->Actions[EPlayerState::Zoom], ETriggerEvent::Completed, this, &AC_GlobalPlayer::AimEnd);
		// Att 
		//EnhancedInputComponent->BindAction(AttAction, ETriggerEvent::Started, this, &AC_NickMainPlayer::PunchAtt);
		//EnhancedInputComponent->BindAction(AttAction, ETriggerEvent::Completed, this, &AC_NickMainPlayer::PunchAttEnd);

		//Fire
		//EnhancedInputComponent->BindAction(InputData->Actions[EPlayerState::Fire], ETriggerEvent::Started, this, &AC_GlobalPlayer::FireStart);
		EnhancedInputComponent->BindAction(InputData->Actions[EPlayerState::Fire], ETriggerEvent::Started, this, &AC_GlobalPlayer::FireStart);
		EnhancedInputComponent->BindAction(InputData->Actions[EPlayerState::Fire], ETriggerEvent::Completed, this, &AC_GlobalPlayer::FireEnd);
		EnhancedInputComponent->BindAction(InputData->Actions[EPlayerState::Fire], ETriggerEvent::Canceled, this, &AC_GlobalPlayer::FireEnd);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AC_GlobalPlayer::Move(const FInputActionValue& Value)
{
	// input is a Vector2D

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AC_GlobalPlayer::GunLineTrace_Implementation()
{
	if (nullptr == CurWeapon)
	{
		return;
	}

	UC_GunComponent* GunMesh = CurWeapon->GetComponentByClass<UC_GunComponent>();

	FHitResult Hit;
	//ector ShotDirection;

	FVector GunLocation = GunMesh->GetSocketLocation(FName("Muzzle"));
	FRotator GunRotation = GunMesh->GetSocketRotation(FName("Muzzle"));
	FVector GunForwardVector =  UKismetMathLibrary::GetForwardVector(GunRotation);
	
	FVector Start = GunLocation;
	FVector End = (GunForwardVector * LineTraceValue) + GunLocation;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(CurWeapon);
	Params.AddIgnoredActor(this);

	TArray<AActor*> Actors;

	Actors.Add(CurWeapon);
	UKismetSystemLibrary::LineTraceSingle(this, Start, End, ETraceTypeQuery::TraceTypeQuery1, false, Actors, EDrawDebugTrace::ForDuration, Hit, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
	//GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_GameTraceChannel1, Params, EDrawDebugTrace::ForDuration);
	//GunRotation.
}



void AC_GlobalPlayer::ResultPitchCal_Implementation(float _Pitch)
{
	PitchCPP = UKismetMathLibrary::FClamp(_Pitch, -30.0f, 30.0f);
}

void AC_GlobalPlayer::LookMove(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>()* UGameplayStatics::GetWorldDeltaSeconds(this) * CameraRotSpeed;

	PitchCPP += LookAxisVector.Y;
	
	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(-LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}

	ResultPitchCal(PitchCPP);
}

void AC_GlobalPlayer::GunLineTraceServer_Implementation()
{
	GunLineTrace();
}

void AC_GlobalPlayer::Calstamina()
{
	
	if (false == IsRunCpp)
	{
		if (stamina == Maxstamina)
		{
			return;
		}
		stamina += staminaCalValue;
	}
	else if (true==IsRunCpp) // 점프 체크 값 추가로 넣어야함
	{
		
		if (true == GetCharacterMovement()->bWantsToCrouch)
		{
			return;
		}

		if (stamina == 0)
		{
			RunEnd_Implementation(0);
			return;
		}
		stamina -= staminaCalValue;
	}
}

void AC_GlobalPlayer::CrouchCpp(const FInputActionValue& Value)
{

	if (true==GetCharacterMovement()->bWantsToCrouch)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void AC_GlobalPlayer::PlayerMeshOption()
{
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
}


void AC_GlobalPlayer::RunStart_Implementation(const FInputActionValue& Value)
{


	if (GetCharacterMovement()->Velocity.Length()<=0)
	{
		return;
	}

	if (stamina == 0)
	{
		return;
	}
	


	GetCharacterMovement()->MaxWalkSpeed = PlayerDT.RunSpeed;

	

	IsRunCpp = true;
}

void AC_GlobalPlayer::AimStart_Implementation(const FInputActionValue& Value)
{
	IsAimCpp = true;
}

void AC_GlobalPlayer::RunEnd_Implementation(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = PlayerDT.WalkSpeed;
	IsRunCpp = false;
}

void AC_GlobalPlayer::AimEnd_Implementation(const FInputActionValue& Value)
{
	IsAimCpp = false;
}

void AC_GlobalPlayer::ChangeSlotMesh_Implementation(EStaticItemSlot _Slot, UStaticMesh* _Mesh)
{
	if (nullptr!=CurWeapon)
	{
		CurWeapon->Destroy();
	}

	uint8 SlotIndex = static_cast<uint8>(_Slot);
	if (StaticItemMesh.Num() <= SlotIndex)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (ItemMeshs.Num() <= static_cast<uint8>(_Slot))"), __FUNCTION__, __LINE__);
		return;
	}

	UEnum* Enum = StaticEnum<ESkerItemSlot>();
	// USkeletalMeshComponent 슬롯 전용
	for (size_t i = 0; i < static_cast<size_t>(ESkerItemSlot::SlotMax); i++)
	{
		SkeletalItemMesh[i]->SetSkeletalMesh(nullptr);
	}

	switch (_Slot)
	{
	case EStaticItemSlot::RSword:
		StaticItemMesh[static_cast<uint8>(EStaticItemSlot::RAxe)]->SetStaticMesh(nullptr);


		PlayerCurState = EWeaponUseState::Sword;
		break;
	case EStaticItemSlot::RAxe:
		break;
	case EStaticItemSlot::SlotMax:
		break;
	default:
		break;
	}


	StaticItemMesh[SlotIndex]->SetStaticMesh(_Mesh);
}

void AC_GlobalPlayer::ChangeSlotMeshServer_Implementation(EStaticItemSlot _Slot, UStaticMesh* _Mesh)
{
	ChangeSlotMesh(_Slot, _Mesh);
}

void AC_GlobalPlayer::ChangeSlotSkeletal_Implementation(ESkerItemSlot _Slot, USkeletalMesh* _Mesh)
{

	uint8 SlotIndex = static_cast<uint8>(_Slot);
	if (SkeletalItemMesh.Num() <= SlotIndex)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (ItemMeshs.Num() <= static_cast<uint8>(_Slot))"), __FUNCTION__, __LINE__);
		return;
	}

	UEnum* Enum = StaticEnum<ESkerItemSlot>();
	// USkeletalMeshComponent 슬롯 전용
	for (size_t i = 0; i < static_cast<size_t>(EStaticItemSlot::SlotMax); i++)
	{
		StaticItemMesh[i]->SetStaticMesh(nullptr);
	}

	switch (_Slot)
	{
	case ESkerItemSlot::LRifle:
		SkeletalItemMesh[static_cast<uint8>(ESkerItemSlot::RPistol)]->SetSkeletalMesh(nullptr);
		SkeletalItemMesh[static_cast<uint8>(ESkerItemSlot::LShotgun)]->SetSkeletalMesh(nullptr);

		PlayerCurState = EWeaponUseState::Rifle;
		break;
	case ESkerItemSlot::RPistol:
		break;
	case ESkerItemSlot::LShotgun:
		break;
	case ESkerItemSlot::SlotMax:
		break;
	default:
		break;
	}

	

	SkeletalItemMesh[SlotIndex]->SetSkeletalMesh(_Mesh);
}

void AC_GlobalPlayer::ChangeSlotSkeletalServer_Implementation(ESkerItemSlot _Slot, USkeletalMesh* _Mesh)
{
	ChangeSlotSkeletal(_Slot, _Mesh);
}

void AC_GlobalPlayer::ChangeNoWeapon_Implementation()
{
	if (PlayerCurState == EWeaponUseState::NoWeapon)
	{
		return;
	}
	

	{
		UEnum* Enum = StaticEnum<ESkerItemSlot>();
		// USkeletalMeshComponent 슬롯 전용
		for (size_t i = 0; i < static_cast<size_t>(ESkerItemSlot::SlotMax); i++)
		{
			SkeletalItemMesh[i]->SetSkeletalMesh(nullptr);
		}

	}

	{
		UEnum* Enum = StaticEnum<ESkerItemSlot>();
		// USkeletalMeshComponent 슬롯 전용
		for (size_t i = 0; i < static_cast<size_t>(EStaticItemSlot::SlotMax); i++)
		{
			StaticItemMesh[i]->SetStaticMesh(nullptr);
		}
	}
	
	PlayerCurState = EWeaponUseState::NoWeapon;
}

void AC_GlobalPlayer::ChangeNoWeaponServer_Implementation()
{
	ChangeNoWeapon();
}

void AC_GlobalPlayer::FireStart_Implementation(const FInputActionValue& Value)
{
	if (true == IsAimCpp)
	{
		IsFireCpp = true;
		GunLineTraceServer();
	}
}

void AC_GlobalPlayer::FireEnd_Implementation(const FInputActionValue& Value)
{
	IsFireCpp = false;
}


void AC_GlobalPlayer::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AC_GlobalPlayer::GetHasRifle()
{
	return bHasRifle;
}

