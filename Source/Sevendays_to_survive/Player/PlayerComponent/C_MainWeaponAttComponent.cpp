// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerComponent/C_MainWeaponAttComponent.h"
#include "Player/Global/C_GlobalPlayer.h"

// Sets default values for this component's properties
UC_MainWeaponAttComponent::UC_MainWeaponAttComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UC_MainWeaponAttComponent::AttStart_Implementation()
{
	
	if (false == IsAttCPP)
	{
		IsAttCPP = true;
		PlayerMesh->GetAnimInstance()->Montage_Play(AttAni);
		IsAttCPP = false;
	}
}

void UC_MainWeaponAttComponent::AttStart2_Implementation()
{
	if (false == IsAttCPP)
	{
		IsAttCPP = true;
		PlayerMesh->GetAnimInstance()->Montage_Play(AttAni2);
		IsAttCPP = false;
	}
}

// Called when the game starts
void UC_MainWeaponAttComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	Player = GetOwner<AC_GlobalPlayer>();
	PlayerMesh = Player->GetMesh();
}


// Called every frame
void UC_MainWeaponAttComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

