// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Component/C_MonsterComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "Monster/C_ZombieBase.h"

// Sets default values for this component's properties
UC_MonsterComponent::UC_MonsterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UC_MonsterComponent::SetData(FTableRowBase* _Data)
{

}

// Called when the game starts
void UC_MonsterComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UC_MonsterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UC_MonsterComponent::Move(FVector _Location)
{
	MonsterPawn->Move(_Location);
}

void UC_MonsterComponent::Run(FVector _Location)
{
	MonsterPawn->Run(_Location);
}

void UC_MonsterComponent::Idle()
{
	MonsterPawn->Idle();
}

void UC_MonsterComponent::Attack()
{
	MonsterPawn->Attack();
}

void UC_MonsterComponent::RunAttack()
{
	MonsterPawn->RunAttack();
}

