// Fill out your copyright notice in the Description page of Project Settings.

#include "Map/C_MapInteractionComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Map/C_ItemSourceHISMA.h"
#include "Map/C_MapInteractable.h"
#include "Map/C_MapDamageTaker.h"
#include "Player/Global/C_MapPlayer.h"
#include "Camera/CameraComponent.h"
#include "STS/C_STSMacros.h"

UC_MapInteractionComponent::UC_MapInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UC_MapInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner<AC_MapPlayer>();
	CameraComponent = Owner->GetComponentByClass<UCameraComponent>();
}

void UC_MapInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UC_MapInteractionComponent::IsServer() const
{
	return UKismetSystemLibrary::IsServer(GetWorld());
}

bool UC_MapInteractionComponent::IsOwnerLocallyControlled() const
{
	return Owner->IsLocallyControlled();
}

FVector UC_MapInteractionComponent::GetHpBarTraceStartPoint() const
{
	FVector CameraLocation = CameraComponent->GetComponentLocation();
	FVector CameraForward = CameraComponent->GetForwardVector();
	return CameraLocation + CameraForward * HpBarTraceStartRange;
}

FVector UC_MapInteractionComponent::GetHpBarTraceEndPoint() const
{
	FVector CameraLocation = CameraComponent->GetComponentLocation();
	FVector CameraForward = CameraComponent->GetForwardVector();
	return CameraLocation + CameraForward * HpBarTraceEndRange;
}

FRotator UC_MapInteractionComponent::GetCameraRotation() const
{
	return CameraComponent->GetComponentRotation();
}

void UC_MapInteractionComponent::ProcessMapDamageableActorTraceResult(FHitResult _HitResult, bool _IsHit)
{
}

void UC_MapInteractionComponent::ProcessItemSourceTraceResult(FHitResult _HitResult, bool _IsHit)
{
	// 아이템 소스를 보지 않게 되는 경우
	if (false == _IsHit)
	{
		if (true == IsValid(ViewingItemSource))
		{
			ViewingItemSource->HideHpBar();
		}
		ViewingItemSource = nullptr;
		return;
	}

	// 같은 아이템 소스를 계속 보는 경우
	if (ViewingItemSource == _HitResult.GetActor())
	{
		ViewingItemSource->UpdateHpBar(_HitResult.Item);
		return;
	}

	// 다른 아이템 소스를 보게 되는 경우
	if (true == IsValid(ViewingItemSource))
	{
		ViewingItemSource->HideHpBar();
	}
	ViewingItemSource = Cast<AC_ItemSourceHISMA>(_HitResult.GetActor());
	ViewingItemSource->UpdateHpBar(_HitResult.Item);
}

void UC_MapInteractionComponent::ProcessItemPouchTraceResult(FHitResult _HitResult, bool _IsHit)
{
	// 아이템 파우치를 보지 않게 되는 경우
	if (false == _IsHit)
	{
		if (true == IsValid(ViewingItemPouch))
		{
			ViewingItemPouch->HideInteractionWidget();
		}

		ViewingItemPouch = nullptr;
		return;
	}

	// 같은 아이템 파우치를 계속 보는 경우
	if (ViewingItemPouch == _HitResult.GetActor())
	{
		ViewingItemPouch->ShowInteractionWidget();
		return;
	}

	// 다른 아이템 파우치를 보게 되는 경우
	if (true == IsValid(ViewingItemPouch))
	{
		ViewingItemPouch->HideInteractionWidget();
	}
	ViewingItemPouch = Cast<AC_MapInteractable>(_HitResult.GetActor());
	ViewingItemPouch->ShowInteractionWidget();
}

void UC_MapInteractionComponent::ProcessHpObjectTraceResult(FHitResult _HitResult, bool _IsHit)
{
	// 건축물을 보지 않게 되는 경우
	if (false == _IsHit)
	{
		if (true == IsValid(ViewingDamageTaker))
		{
			ViewingDamageTaker->HideHpBar();
		}
		ViewingDamageTaker = nullptr;
		return;
	}

	// 같은 건축물을 계속 보는 경우
	if (ViewingDamageTaker == _HitResult.GetActor())
	{
		ViewingDamageTaker->UpdateHpBar();
		return;
	}

	// 다른 건축물을 보게 되는 경우
	if (true == IsValid(ViewingDamageTaker))
	{
		ViewingDamageTaker->HideHpBar();
	}
	ViewingDamageTaker = Cast<AC_MapDamageTaker>(_HitResult.GetActor());
	ViewingDamageTaker->UpdateHpBar();
}

void UC_MapInteractionComponent::DestroyActor_Implementation(AActor* _Actor)
{
	_Actor->Destroy();
}
