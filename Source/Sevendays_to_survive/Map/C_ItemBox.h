// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map/C_MapDamageTaker.h"
#include "C_ItemBox.generated.h"

class UC_HealthBar;
class AC_ItemPouch;
class UC_MapDataAsset;

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_ItemBox : public AC_MapDamageTaker
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

private:
    void PreDestroy() override;

    // 아이템 스폰
    UFUNCTION(Server, Reliable)
    void SpawnItems();
    void SpawnItems_Implementation();

    UC_MapDataAsset* MapDataAsset = nullptr;

    TSubclassOf<AC_ItemPouch> ItemPouchClass = nullptr;
};
