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
#include "Components/ChildActorComponent.h"
#include "Animation/AnimMontage.h"
#include "Player/Input/C_InputActionDatas.h"


// Sets default values
AC_GlobalPlayer::AC_GlobalPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	//PlayerDT = STSInstance->GetPlayerDataTable();
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
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
	SpringArm->SetupAttachment(RootComponent);
	//SpringArm->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a camera boom (pulls in towards the player if there is a collision)
	TPSZoomSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TPSZoomSpringArm"));
	TPSZoomSpringArm->SetupAttachment(RootComponent);
	TPSZoomSpringArm->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	TPSZoomSpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	TPSZoomCamera = CreateDefaultSubobject<UChildActorComponent>(TEXT("TPSZoomCamera"));
	TPSZoomCamera->SetupAttachment(TPSZoomSpringArm); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation

	// Create a camera boom (pulls in towards the player if there is a collision)
	FPSSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("FPSSpringArm"));
	FPSSpringArm->SetupAttachment(RootComponent);
	FPSSpringArm->TargetArmLength = 200.0f; // The camera follows at this distance behind the character	
	FPSSpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FPSCamera = CreateDefaultSubobject<UChildActorComponent>(TEXT("FPSCamera"));
	FPSCamera->SetupAttachment(FPSSpringArm);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(Camera);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	// Create a camera boom (pulls in towards the player if there is a collision)
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	UEnum* Enum = StaticEnum<EPlayerItemSlot>();

	for (size_t i = 1; i < static_cast<size_t>(EPlayerItemSlot::SlotMax); i++)
	{
		FString Name = Enum->GetNameStringByValue(i);
		UStaticMeshComponent* NewSlotMesh = CreateDefaultSubobject<UStaticMeshComponent>(*Name);
		NewSlotMesh->SetupAttachment(GetMesh(), *Name);

		ItemMeshs.Push(NewSlotMesh);
	}

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
}

// Called when the game starts or when spawned
void AC_GlobalPlayer::BeginPlay()
{
	Super::BeginPlay();
	UC_STSInstance* STSInstance = GetWorld()->GetGameInstanceChecked<UC_STSInstance>();
	CameraDT = STSInstance->GetPlayerDataTable()->CameraValue;
	PlayerDT = STSInstance->GetPlayerDataTable()->PlayerValue;
	
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
		stamina = PlayerDT.stamina;
		Hp = PlayerDT.Hp;
	}
	
	//Add Input Mapping Context
	if (AC_MainPlayerController* PlayerController = Cast<AC_MainPlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void AC_GlobalPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		EnhancedInputComponent->BindAction(InputData->Actions[EPlayerState::Look], ETriggerEvent::Triggered, this, &AC_GlobalPlayer::Look);

		//Crouch
		EnhancedInputComponent->BindAction(InputData->Actions[EPlayerState::Crouch], ETriggerEvent::Started, this, &AC_GlobalPlayer::CrouchCpp);
		// Att 
		//EnhancedInputComponent->BindAction(AttAction, ETriggerEvent::Started, this, &AC_NickMainPlayer::PunchAtt);
		//EnhancedInputComponent->BindAction(AttAction, ETriggerEvent::Completed, this, &AC_NickMainPlayer::PunchAttEnd);
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

void AC_GlobalPlayer::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>() * UGameplayStatics::GetWorldDeltaSeconds(this) * CameraRotSpeed;

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(-LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
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

void AC_GlobalPlayer::RunStart_Implementation(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = PlayerDT.RunSpeed;
	IsRunCpp = true;
}

void AC_GlobalPlayer::RunEnd_Implementation(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = PlayerDT.WalkSpeed;
	IsRunCpp = false;
}

void AC_GlobalPlayer::ChangeSlotMesh(EPlayerItemSlot _Slot, UStaticMesh* _Mesh)
{
	uint8 SlotIndex = static_cast<uint8>(_Slot);
	if (ItemMeshs.Num() <= SlotIndex)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (ItemMeshs.Num() <= static_cast<uint8>(_Slot))"), __FUNCTION__, __LINE__);
		return;
	}

	ItemMeshs[SlotIndex]->SetStaticMesh(_Mesh);
}

void AC_GlobalPlayer::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AC_GlobalPlayer::GetHasRifle()
{
	return bHasRifle;
}

