// Fill out your copyright notice in the Description page of Project Settings.

#include "Map/C_MapInteractionComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Map/C_ItemSourceHISMA.h"
#include "Map/C_MapInteractable.h"
#include "Map/C_MapDamageTaker.h"
#include "BuildingSystem/C_Door.h"
#include "Player/Global/C_MapPlayer.h"
#include "Camera/CameraComponent.h"
#include "STS/C_STSMacros.h"
#include "BuildingSystem/C_Door.h"

UC_MapInteractionComponent::UC_MapInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UC_MapInteractionComponent::BeginPlay()
{
    Super::BeginPlay();

    Owner = GetOwner<AC_MapPlayer>();
    CameraComponent = Owner->GetComponentByClass<UCameraComponent>();

    IsInteractingMap.Emplace(EMapInteractionTarget::ItemSource, false);
    IsInteractingMap.Emplace(EMapInteractionTarget::MapDamageTaker, false);
    IsInteractingMap.Emplace(EMapInteractionTarget::ItemPouch, false);
    IsInteractingMap.Emplace(EMapInteractionTarget::Door, false);
}

void UC_MapInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (false == IsOwnerLocallyControlled())
    {
        return;
    }

    ResetIsInteractingMap();

    TArray<FHitResult> OutHits;

    bool IsHit = UKismetSystemLibrary::BoxTraceMulti(
        GetWorld(),
        GetTraceStartPoint(),
        GetTraceEndPoint(),
        BoxHalfSize,
        FRotator::ZeroRotator,
        UEngineTypes::ConvertToTraceType(ECC_Visibility),
        false,
        TArray{ GetOwner() },
        EDrawDebugTrace::None,
        OutHits,
        true
    );

    for (FHitResult& OutHit : OutHits)
    {
        if (true == OutHit.GetActor()->IsA<AC_ItemSourceHISMA>())
        {
            IsInteractingMap[EMapInteractionTarget::ItemSource] = true;
            ViewItemSource(Cast<AC_ItemSourceHISMA>(OutHit.GetActor()), OutHit.Item);
        }
        if (true == OutHit.GetActor()->IsA<AC_MapDamageTaker>())
        {
            IsInteractingMap[EMapInteractionTarget::MapDamageTaker] = true;
            ViewMapDamageTaker(Cast<AC_MapDamageTaker>(OutHit.GetActor()));
        }
        if (true == OutHit.GetActor()->IsA<AC_MapInteractable>())
        {
            IsInteractingMap[EMapInteractionTarget::ItemPouch] = true;
            ViewItemPouch(Cast<AC_MapInteractable>(OutHit.GetActor()));
        }
        if (true == OutHit.GetActor()->IsA<AC_Door>())
        {
            IsInteractingMap[EMapInteractionTarget::Door] = true;
            ViewDoor(Cast<AC_Door>(OutHit.GetActor()));
        }
    }

    for (auto& Pair : IsInteractingMap)
    {
        if (false == Pair.Value)
        {
            switch (Pair.Key)
            {
            case EMapInteractionTarget::ItemSource:
                UnviewItemSource();
                break;
            case EMapInteractionTarget::MapDamageTaker:
                UnviewMapDamageTaker();
                break;
            case EMapInteractionTarget::ItemPouch:
                UnviewItemPouch();
                break;
            case EMapInteractionTarget::Door:
                UnviewDoor();
                break;
            default:
                break;
            }
        }
    }
}

void UC_MapInteractionComponent::DoorInteraction_Implementation(AC_Door* _Door)
{
    _Door->OpenOrClose();
}

bool UC_MapInteractionComponent::IsServer() const
{
    return UKismetSystemLibrary::IsServer(GetWorld());
}

bool UC_MapInteractionComponent::IsOwnerLocallyControlled() const
{
    return Owner->IsLocallyControlled();
}

FVector UC_MapInteractionComponent::GetTraceStartPoint() const
{
    FVector CameraLocation = CameraComponent->GetComponentLocation();
    FVector CameraForward = CameraComponent->GetForwardVector();
    return CameraLocation + CameraForward * TraceStartRange;
}

FVector UC_MapInteractionComponent::GetTraceEndPoint() const
{
    FVector CameraLocation = CameraComponent->GetComponentLocation();
    FVector CameraForward = CameraComponent->GetForwardVector();
    return CameraLocation + CameraForward * TraceEndRange;
}

FRotator UC_MapInteractionComponent::GetCameraRotation() const
{
    return CameraComponent->GetComponentRotation();
}

void UC_MapInteractionComponent::OnMapInteractionKeyDown()
{
    if (true == IsValid(ViewingItemPouch))
    {
        ViewingItemPouch->MapInteract();
        return;
    }

    if (true == IsValid(ViewingDoor))
    {
        ViewingDoor->MapInteract();
        return;
    }
}

void UC_MapInteractionComponent::ResetIsInteractingMap()
{
    for (TPair<EMapInteractionTarget, bool>& Pair : IsInteractingMap)
    {
        IsInteractingMap[Pair.Key] = false;
    }
}

void UC_MapInteractionComponent::DestroyActor_Implementation(AActor* _Actor)
{
    if (nullptr == _Actor)
    {
        return;
    }

    _Actor->Destroy();
}


void UC_MapInteractionComponent::ViewItemSource(AC_ItemSourceHISMA* _ItemSource, int _Index)
{
    // 같은 아이템 소스를 계속 보는 경우
    if (ViewingItemSource == _ItemSource)
    {
        ViewingItemSource->UpdateHpBar(_Index);
        return;
    }

    // 다른 아이템 소스를 보게 되는 경우
    if (true == IsValid(ViewingItemSource))
    {
        ViewingItemSource->HideHpBar();
    }
    ViewingItemSource = _ItemSource;
    if (true == IsValid(ViewingItemSource))
    {
        ViewingItemSource->UpdateHpBar(_Index);
    }
}

void UC_MapInteractionComponent::ViewMapDamageTaker(AC_MapDamageTaker* _DamageTaker)
{
    // 같은 건축물을 계속 보는 경우
    if (ViewingDamageTaker == _DamageTaker)
    {
        ViewingDamageTaker->UpdateHpBar();
        return;
    }

    // 다른 건축물을 보게 되는 경우
    if (true == IsValid(ViewingDamageTaker))
    {
        ViewingDamageTaker->HideHpBar();
    }
    ViewingDamageTaker = _DamageTaker;
    if (true == IsValid(ViewingDamageTaker))
    {
        ViewingDamageTaker->UpdateHpBar();
    }
}

void UC_MapInteractionComponent::ViewItemPouch(AC_MapInteractable* _MapInteractable)
{
    // 같은 아이템 파우치를 계속 보는 경우
    if (ViewingItemPouch == _MapInteractable)
    {
        ViewingItemPouch->ShowInteractionWidget();
        return;
    }

    // 다른 아이템 파우치를 보게 되는 경우
    if (true == IsValid(ViewingItemPouch))
    {
        ViewingItemPouch->HideInteractionWidget();
    }
    ViewingItemPouch = _MapInteractable;
    if (true == IsValid(ViewingItemPouch))
    {
        ViewingItemPouch->ShowInteractionWidget();
    }
}

void UC_MapInteractionComponent::ViewDoor(AC_Door* _Door)
{
    // 같은 문을 계속 보는 경우
    if (ViewingDoor == _Door)
    {
        //ViewingDoor->ShowInteractionWidget();
        return;
    }

    // 다른 문을 보게 되는 경우
    if (true == IsValid(ViewingDoor))
    {
        //ViewingDoor->HideInteractionWidget();
    }
    ViewingDoor = _Door;
}

void UC_MapInteractionComponent::UnviewItemSource()
{
    if (true == IsValid(ViewingItemSource))
    {
        ViewingItemSource->HideHpBar();
    }
    ViewingItemSource = nullptr;
}

void UC_MapInteractionComponent::UnviewMapDamageTaker()
{
    if (true == IsValid(ViewingDamageTaker))
    {
        ViewingDamageTaker->HideHpBar();
    }
    ViewingDamageTaker = nullptr;
}

void UC_MapInteractionComponent::UnviewItemPouch()
{
    if (true == IsValid(ViewingItemPouch))
    {
        ViewingItemPouch->HideInteractionWidget();
    }

    ViewingItemPouch = nullptr;
}

void UC_MapInteractionComponent::UnviewDoor()
{
    if (true == IsValid(ViewingDoor))
    {
        //ViewingDoor->HideInteractionWidget();
    }

    ViewingDoor = nullptr;
}
