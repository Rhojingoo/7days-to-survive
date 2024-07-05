// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_GunComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/Global/C_GlobalPlayer.h"
#include "Player/Global/C_PlayerEnum.h"

UC_GunComponent::UC_GunComponent()
{
	// Default offset from the character location for projectiles to spawn
	//MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UC_GunComponent::AttachWeapon(AC_GlobalPlayer* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no rifle yet
	if (Character == nullptr /*|| Character->GetHasRifle()*/)
	{
		return;
	}
	Character->SetPlayerCurState(EWeaponUseState::Rifle);
	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

	if (Character->GetSkeletalItemMesh()[static_cast<uint8>(ESkerItemSlot::LRifle)]->SkeletalMesh == nullptr)
	{
		AttachToComponent(Character->GetSkeletalItemMesh()[static_cast<uint8>(ESkerItemSlot::LRifle)], AttachmentRules, FName(TEXT("LRifle")));

		// switch bHasRifle so the animation blueprint can switch to another animation set
		Character->SetHasRifle(true);
	}

	

	//// Set up action bindings
	//if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	//{
	//	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	//	{
	//		// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
	//		Subsystem->AddMappingContext(FireMappingContext, 1);
	//	}

	//	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
	//	{
	//		// Fire
	//		//EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UC_GunComponent::Fire);
	//	}
	//}
}

void UC_GunComponent::AttachPistol1(AC_GlobalPlayer* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no rifle yet
	if (Character == nullptr /*|| Character->GetHasRifle()*/)
	{
		return;
	}
	Character->SetPlayerCurState(EWeaponUseState::Pistol);
	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

	if (Character->GetSkeletalItemMesh()[static_cast<uint8>(ESkerItemSlot::RPistol)]->SkeletalMesh == nullptr)
	{
		AttachToComponent(Character->GetSkeletalItemMesh()[static_cast<uint8>(ESkerItemSlot::RPistol)], AttachmentRules, FName(TEXT("RPistol")));

		// switch bHasRifle so the animation blueprint can switch to another animation set
		Character->SetHasRifle(true);
	}
}

void UC_GunComponent::AttachShotGun(AC_GlobalPlayer* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no rifle yet
	if (Character == nullptr /*|| Character->GetHasRifle()*/)
	{
		return;
	}
	Character->SetPlayerCurState(EWeaponUseState::Shotgun);
	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

	if (Character->GetSkeletalItemMesh()[static_cast<uint8>(ESkerItemSlot::LShotgun)]->SkeletalMesh == nullptr)
	{
		AttachToComponent(Character->GetSkeletalItemMesh()[static_cast<uint8>(ESkerItemSlot::LShotgun)], AttachmentRules, FName(TEXT("LShotgun")));

		// switch bHasRifle so the animation blueprint can switch to another animation set
		Character->SetHasRifle(true);
	}
}
