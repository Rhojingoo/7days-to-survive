// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "C_MonsterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SEVENDAYS_TO_SURVIVE_API UC_MonsterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_MonsterComponent();


	void SetController(class AAIController* _Controller) {
		Controller = _Controller;
	}

	void SetMonster(class AC_ZombieBase* _Monster) {
		MonsterPawn = _Monster;
	}

	void SetData(FTableRowBase* _Data);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/*void Attack();
	void Dead();
	void Run();*/
	void Move(FVector _Location);
	void Idle();

private:
	void Init();
	UPROPERTY()
	const AAIController* Controller = nullptr;

	const FTableRowBase* MonsterData = nullptr; 

	UPROPERTY()
	AC_ZombieBase* MonsterPawn = nullptr;
};
