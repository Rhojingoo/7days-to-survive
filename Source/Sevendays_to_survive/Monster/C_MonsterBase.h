// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_MonsterBase.generated.h"

UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_MonsterBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AC_MonsterBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")		// Ai �ൿ ������
	class UBehaviorTree* AITree;													// ��Ʈ�ѷ��� �ൿ �����ڴ� �ٸ�����

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
