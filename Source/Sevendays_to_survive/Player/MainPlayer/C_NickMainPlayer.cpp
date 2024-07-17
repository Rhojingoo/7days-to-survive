// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainPlayer/C_NickMainPlayer.h"
#include "Player/Global/C_GlobalAnimInstance.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Player/Global/C_PlayerEnum.h"
#include "Player/Input/C_InputActionDatas.h"
#include "Components/ArrowComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Components/CapsuleComponent.h"





AC_NickMainPlayer::AC_NickMainPlayer()
{
	LocationComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("LocationComponent"));
	LocationComponent->SetupAttachment(RootComponent); // RootComponent에 부착
}

FVector AC_NickMainPlayer::GetComponentLocation()
{
	FVector Location = LocationComponent->GetComponentLocation();
	return Location;
}

void AC_NickMainPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//DOREPLIFETIME(AC_NickMainPlayer, MontageToPlay);
}

void AC_NickMainPlayer::BeginPlay()
{
	Super::BeginPlay();

}

void AC_NickMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_NickMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

AActor* AC_NickMainPlayer::SpawnMapCamera(const FTransform& _Transform)
{
	if (MapCameraComponent == nullptr) {
		UE_LOG(LogTemp, Fatal, TEXT(""));
	}
	if (GetController() == UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
		AActor* Camera = GetWorld()->SpawnActor(MapCameraComponent, &_Transform);
		if (nullptr == Camera) {
			UE_LOG(LogTemp, Fatal, TEXT(""));
		}
		FAttachmentTransformRules AttachRule(EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, true);
		Camera->AttachToComponent(GetCapsuleComponent(), AttachRule);
		return Camera;
	}
	return nullptr;
}

