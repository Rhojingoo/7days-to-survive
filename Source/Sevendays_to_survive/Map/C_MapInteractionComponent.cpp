// Fill out your copyright notice in the Description page of Project Settings.

#include "Map/C_MapInteractionComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Map/C_ItemSourceHISMA.h"
#include "Map/C_MapInteractable.h"
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

void UC_MapInteractionComponent::ProcessItemSourceTraceResult(FHitResult _HitResult, bool _IsHit)
{
	// ������ �ҽ��� ���� �ʰ� �Ǵ� ���
	if (false == _IsHit)
	{
		if (true == IsValid(ViewingItemSource))
		{
			ViewingItemSource->HideHpBar();
		}
		ViewingItemSource = nullptr;
		return;
	}

	// ���� ������ �ҽ��� ��� ���� ���
	if (ViewingItemSource == _HitResult.GetActor())
	{
		ViewingItemSource->UpdateHpBar(_HitResult.Item);
		return;
	}

	// �ٸ� ������ �ҽ��� ���� �Ǵ� ���
	if (true == IsValid(ViewingItemSource))
	{
		ViewingItemSource->HideHpBar();
	}
	ViewingItemSource = Cast<AC_ItemSourceHISMA>(_HitResult.GetActor());
	ViewingItemSource->UpdateHpBar(_HitResult.Item);
}

void UC_MapInteractionComponent::ProcessItemPouchTraceResult(FHitResult _HitResult, bool _IsHit)
{
	if (true == _IsHit)
	{
		AC_MapInteractable* ItemPouch = Cast<AC_MapInteractable>(_HitResult.GetActor());
		if (false == IsValid(ItemPouch))
		{
			STS_FATAL("[%s] Given actor is not map interactable or invalid.", __FUNCTION__);
		}
		ViewingItemPouch = ItemPouch;
		ViewingItemPouch->ShowInteractionWidget();
		return;
	}

	if (true == IsValid(ViewingItemPouch))
	{
		ViewingItemPouch->HideInteractionWidget();
	}

	ViewingItemPouch = nullptr;
}
