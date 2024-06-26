// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerComponent/C_PunchAttComponent.h"
#include "Player/MainPlayer/C_NickMainPlayer.h"
//#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UC_PunchAttComponent::UC_PunchAttComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UC_PunchAttComponent::AttStart_Implementation()
{
	if (false == IsAttCPP)
	{
		IsAttCPP = true;
		FTimerHandle MyTimerHandle;
		switch (ComboCPP)
		{
		case 0:
			PlayerMesh->GetAnimInstance()->Montage_Play(AttAni[ComboCPP]);
			IsAttCPP = false;
			ComboCPP = 1;
			//Player->GetWorldTimerManager().SetTimer(MyTimerHandle, this, &UC_PunchAttComponent::AttStart_Implementation, 1.0f, false, false);
			//UKismetSystemLibrary::K2_SetTimer(this, "ComboCPP1", 1.0f);
			break;
		case 1:
			PlayerMesh->GetAnimInstance()->Montage_Play(AttAni[ComboCPP]);
			IsAttCPP = false;
			ComboCPP = 2;
			//Player->GetWorldTimerManager().SetTimer(MyTimerHandle, this, &UC_PunchAttComponent::AttStart_Implementation, 1.0f, false, false);
			break;
		case 2:
			PlayerMesh->GetAnimInstance()->Montage_Play(AttAni[ComboCPP]);
			IsAttCPP = false;
			ComboCPP = 0;
			//Player->GetWorldTimerManager().SetTimer(MyTimerHandle, this, &UC_PunchAttComponent::AttStart_Implementation, 1.0f, false, false);
			break;
		default:
			break;
		}
	}
}

// Called when the game starts
void UC_PunchAttComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Player = GetOwner<AC_NickMainPlayer>();
	PlayerMesh = Player->GetMesh();
	
	AttAni.SetNum(3);
	
}


// Called every frame
void UC_PunchAttComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

