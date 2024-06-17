// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Global/C_GlobalPlayer.h"
#include "STS/C_STSInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values
AC_GlobalPlayer::AC_GlobalPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));


	// 언리얼에서는 회전에서 벡터를 사용하지 않고
	// Rotator Quat의 두가지가 있습니다.
	// 상호보환적 관계 -> Rotator
	// 당연히 우리가 알고 있는 그냥 각도에서 FQuat FRotator
	// Euler Degree

	//FQuat Quat;
	FRotator Rotator;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));


	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->bDoCollisionTest = false;

	GetCharacterMovement();

}

// Called when the game starts or when spawned
void AC_GlobalPlayer::BeginPlay()
{
	Super::BeginPlay();

	STSInstance=GetWorld()->GetGameInstanceChecked<UC_STSInstance>();
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

}

