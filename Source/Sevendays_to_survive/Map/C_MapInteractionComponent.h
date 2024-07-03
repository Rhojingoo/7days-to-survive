// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_MapInteractionComponent.generated.h"

class AC_ItemSourceHISMA;
class AC_ItemPouch;
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

    UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction))
    void DamageItemSource(AC_ItemSourceHISMA* _ItemSource, int _Index, int _Damage);

private:
    // Deprecated. 동기화 방식 변경으로 인해 더이상 사용하지 않지만 혹시 모를 상황을 위해 남겨둔 함수.
    UFUNCTION(Server, Reliable, meta = (DeprecatedFunction))
    void Server_DamageItemSource(APlayerController* _CallingController, AC_ItemSourceHISMA* _ItemSource, int _Index, int _Damage);

    void Server_DamageItemSource_Implementation(APlayerController* _CallingController, AC_ItemSourceHISMA* _ItemSource, int _Index, int _Damage);

    // Deprecated. 동기화 방식 변경으로 인해 더이상 사용하지 않지만 혹시 모를 상황을 위해 남겨둔 함수.
    UFUNCTION(NetMulticast, Reliable, meta = (DeprecatedFunction))
    void Multicast_DamageItemSource(APlayerController* _CallingController, AC_ItemSourceHISMA* _ItemSource, int _Index, int _Damage);

    void Multicast_DamageItemSource_Implementation(APlayerController* _CallingController, AC_ItemSourceHISMA* _ItemSource, int _Index, int _Damage);

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
    void ProcessItemSourceTraceResult(FHitResult _HitResult, bool _IsHit);

    UFUNCTION(BlueprintCallable)
    void ProcessItemPouchTraceResult(FHitResult _HitResult, bool _IsHit);

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
    AC_ItemPouch* ViewingItemPouch = nullptr;
};
