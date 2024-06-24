// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_TaskMonsterPatrol.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"

// 주어진 반경 내에서 랜덤 벡터를 반환하는 함수
FVector UC_TaskMonsterPatrol::GetRandomVectorInRadius(const FVector& Origin, float Radius)
{
    // 구 내부의 랜덤 위치를 생성
    FVector RandomUnitVector = UKismetMathLibrary::RandomUnitVector();
    float RandomDistance = FMath::FRandRange(0.0f, Radius);

    return Origin + RandomUnitVector * RandomDistance;
}

// 사용 예제
void UC_TaskMonsterPatrol::ExampleUsage()
{
    FVector Origin = FVector(0.0f, 0.0f, 0.0f); // 자기 자신의 위치 (예: 현재 Actor의 위치)
    float Radius = 100.0f; // 반경
    FVector RandomVector = GetRandomVectorInRadius(Origin, Radius);
    UE_LOG(LogTemp, Log, TEXT("Random Vector in Radius: %s"), *RandomVector.ToString());
}
