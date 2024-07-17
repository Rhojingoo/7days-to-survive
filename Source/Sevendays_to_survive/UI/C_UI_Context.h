// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/C_UIEnumClass.h"
#include "C_UI_Context.generated.h"

class AC_UI_InGameHUD;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SEVENDAYS_TO_SURVIVE_API UC_UI_Context : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_UI_Context();

	UFUNCTION(BlueprintCallable)
	void UIVisibilitySwitch(EUIType _Type);

	UFUNCTION(BlueprintCallable)
	void UIVisibilityOn(EUIType _Type);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AC_UI_InGameHUD* InGameHUD = nullptr;
};
