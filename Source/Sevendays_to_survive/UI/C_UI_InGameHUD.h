// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "C_UI_InGameHUD.generated.h"


/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_UI_InGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override; //주요 드로 콜

protected:

	
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;

	
};
