// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"

#include "C_MapInteractable.generated.h"

class UC_MapInteractionWidget;

UCLASS(Abstract, BlueprintType)
class SEVENDAYS_TO_SURVIVE_API AC_MapInteractable : public AActor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	AC_MapInteractable();

	UFUNCTION(BlueprintCallable)
	virtual void MapInteract() PURE_VIRTUAL(MapInteract, )

	UFUNCTION(BlueprintCallable)
	virtual void ShowInteractionWidget();

	UFUNCTION(BlueprintCallable)
	virtual void HideInteractionWidget();

private:
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* MapInteractionWidgetComponent = nullptr;

	UC_MapInteractionWidget* MapInteractionWidget = nullptr;
};
