// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MonsterDataRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMonsterDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float SightRange = 0.0f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float AttackRange = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Att = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double HP = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double PatrolTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PatrolCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PatrolMinRange = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PatrolMaxRange = 0;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TMap<FMonsterDataRow, class UAnimMontage* > AnimMontages;
};

UCLASS()
class UMonsterDataObject : public UObject
{
	GENERATED_BODY()

public:
	const FMonsterDataRow* Data;

	TArray<FVector> PatrolPoints;

	float IdleTime = 0.0f;

	float AttackTime = 0.0f;

	FVector OriginPos = FVector::ZeroVector;

	FVector TargetPos;

	//bool IsPatrol();

	//FORCEINLINE void TargetPosToOriginPos()
	//{
	//	TargetPos = OriginPos;
	//}
};
