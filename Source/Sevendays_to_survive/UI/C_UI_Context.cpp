// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_UI_Context.h"

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

	// ...
	
}


// Called every frame
void UC_UI_Context::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UC_UI_Context::UIVisibilitySwitch()
{

}

void UC_UI_Context::UIVisibilityOn()
{
}
