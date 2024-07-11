// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map/C_MapActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "C_ItemBox.generated.h"

class UC_HealthBar;
class AC_ItemPouch;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_ItemBox : public AC_MapActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AC_ItemBox();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

public:
    void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

    float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    UFUNCTION(NetMulticast, Reliable)
    void ReceiveDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
    void ReceiveDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

    UFUNCTION(BlueprintCallable)
    void UpdateHpBar();

    UFUNCTION(BlueprintCallable)
    void HideHpBar();

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* SMComponent = nullptr;

    // 체력바
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float Hp = 100.0f;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float MaxHp = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float HpBarHeight = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    UWidgetComponent* HpBar = nullptr;

    UC_HealthBar* HpBarWidget = nullptr;

private:
    // 아이템 스폰

    UFUNCTION(Server, Reliable)
    void SpawnItems();
    void SpawnItems_Implementation();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TMap<FName, int> DropItems;

    TSubclassOf<AC_ItemPouch> ItemPouchClass = nullptr;
};
