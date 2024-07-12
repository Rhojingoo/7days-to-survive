// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "C_7Days_Play_GameMode.generated.h"

class UTimelineComponent;
class ALight;
class AC_ItemBox;

/**
 *
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_7Days_Play_GameMode : public AGameMode
{
    GENERATED_BODY()

public:
    AC_7Days_Play_GameMode();

    void BeginPlay() override;

    void Tick(float _DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    bool IsServer = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AC_ItemBox> ItemBoxClass = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    int ItemBoxSpawnCountPerArea = 2;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    int ItemBoxSpawnRowCount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    int ItemBoxSpawnColumnCount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    int ItemBoxSpawnBorderWidth = 2;

    const FVector2D EndingPoint = { -53600.0f, 2430.0f };
    const FBox2D TotalArea = FBox2D{ {-89000, -43800}, {9000, 34000} };
};
