// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_MapInteractionComponent.generated.h"

class AC_ItemSourceHISMA;
class AC_MapInteractable;
class AC_BuildingPart;
class AC_MapPlayer;
class UCameraComponent;

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

private:
    UFUNCTION(BlueprintPure)
    bool IsServer() const;

    UFUNCTION(BlueprintPure)
    bool IsOwnerLocallyControlled() const;

    UFUNCTION(BlueprintPure)
    FVector GetHpBarTraceStartPoint() const;

    UFUNCTION(BlueprintPure)
    FVector GetHpBarTraceEndPoint() const;

    UFUNCTION(BlueprintPure)
    FRotator GetCameraRotation() const;

    UFUNCTION(BlueprintCallable)
    void ProcessMapDamageableActorTraceResult(FHitResult _HitResult, bool _IsHit);

    UFUNCTION(BlueprintCallable)
    void ProcessItemSourceTraceResult(FHitResult _HitResult, bool _IsHit);

    UFUNCTION(BlueprintCallable)
    void ProcessItemPouchTraceResult(FHitResult _HitResult, bool _IsHit);

    UFUNCTION(BlueprintCallable)
    void ProcessBuildingPartTraceResult(FHitResult _HitResult, bool _IsHit);

private:
    UPROPERTY(Category = "HpBar", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float HpBarTraceStartRange = 400.0f;

    UPROPERTY(Category = "HpBar", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float HpBarTraceEndRange = 800.0f;


    UPROPERTY(Category = "HpBar", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FVector HpBarLineTraceBoxSize = {100.0f, 100.0f, 100.0f};

    AC_MapPlayer* Owner = nullptr;
    UCameraComponent* CameraComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    AC_ItemSourceHISMA* ViewingItemSource = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    AC_MapInteractable* ViewingItemPouch = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    AC_BuildingPart* ViewingBuildingPart = nullptr;
};
