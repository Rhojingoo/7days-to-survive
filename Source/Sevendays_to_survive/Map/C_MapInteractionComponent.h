// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_MapInteractionComponent.generated.h"

class AC_ItemSourceHISMA;
class AC_MapInteractable;
class AC_MapPlayer;
class AC_MapDamageTaker;
class AC_Door;
class UCameraComponent;

enum class EMapInteractionTarget : uint8
{
    ItemSource,
    MapDamageTaker,
    ItemPouch,
    Door,
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SEVENDAYS_TO_SURVIVE_API UC_MapInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UC_MapInteractionComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
    UFUNCTION(BlueprintCallable, Server, Reliable)
    void DestroyActor(AActor* _Actor);
    void DestroyActor_Implementation(AActor* _Actor);

    UFUNCTION(BlueprintCallable, Server, Reliable)
    void DoorInteraction(AC_Door* _Door);
    void DoorInteraction_Implementation(AC_Door* _Door);

private:
    UFUNCTION(BlueprintPure)
    bool IsServer() const;

    UFUNCTION(BlueprintPure)
    bool IsOwnerLocallyControlled() const;

    UFUNCTION(BlueprintPure)
    FVector GetTraceStartPoint() const;

    UFUNCTION(BlueprintPure)
    FVector GetTraceEndPoint() const;

    UFUNCTION(BlueprintPure)
    FRotator GetCameraRotation() const;

    UFUNCTION(BlueprintCallable)
    void OnMapInteractionKeyDown();

private:
    UPROPERTY(Category = "HpBar", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float TraceStartRange = 200.0f;

    UPROPERTY(Category = "HpBar", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float TraceEndRange = 800.0f;

    UPROPERTY(Category = "HpBar", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FVector BoxHalfSize = { 50.0f, 50.0f, 50.0f };

    AC_MapPlayer* Owner = nullptr;
    UCameraComponent* CameraComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    AC_ItemSourceHISMA* ViewingItemSource = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    AC_MapInteractable* ViewingItemPouch = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    AC_MapDamageTaker* ViewingDamageTaker = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    AC_Door* ViewingDoor = nullptr;

private:
    void ViewItemSource(AC_ItemSourceHISMA* _ItemSource, int _Index);
    void ViewMapDamageTaker(AC_MapDamageTaker* _DamageTaker);
    void ViewItemPouch(AC_MapInteractable* _MapInteractable);
    void ViewDoor(AC_Door* _DamageTaker);

    void UnviewItemSource();
    void UnviewMapDamageTaker();
    void UnviewItemPouch();
    void UnviewDoor();

    void ResetIsInteractingMap();

    TMap<EMapInteractionTarget, bool> IsInteractingMap;
};
