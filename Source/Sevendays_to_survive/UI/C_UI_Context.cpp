// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_UI_Context.h"
#include "UI/C_UI_InGameHUD.h"
#include "STS/C_STSMacros.h"

// Sets default values for this component's properties
UC_UI_Context::UC_UI_Context()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UC_UI_Context::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// UI가 입력과 관련이 많기 때문에 HUD를 찾아내려면 
	InGameHUD = Cast<AC_UI_InGameHUD>(PC->GetHUD());

	if (nullptr == InGameHUD)
	{
		STS_FATAL("[%s] InGameHUD is null.", __FUNCTION__);
		return;
	}
	
}


// Called every frame
void UC_UI_Context::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UC_UI_Context::UIVisibilitySwitch(EUIType _Type)
{
	if (false == IsValid(InGameHUD))
	{
		return;
	}

	InGameHUD->UIVisibilitySwitch(_Type);
}

void UC_UI_Context::UIVisibilityOn(EUIType _Type)
{
	if (false == IsValid(InGameHUD))
	{
		return;
	}

	InGameHUD->UIOn(_Type);
}
