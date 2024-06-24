// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerComponent/C_PunchAttComponent.h"
#include "Player/MainPlayer/C_NickMainPlayer.h"

// Sets default values for this component's properties
UC_PunchAttComponent::UC_PunchAttComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UC_PunchAttComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Player = GetOwner<AC_NickMainPlayer>();
	PlayerMesh = Player->GetMesh();
	
	
}


// Called every frame
void UC_PunchAttComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

