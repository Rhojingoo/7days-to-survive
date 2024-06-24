// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/MonsterTask/C_TaskMonsterPatrol.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"

// �־��� �ݰ� ������ ���� ���͸� ��ȯ�ϴ� �Լ�
FVector UC_TaskMonsterPatrol::GetRandomVectorInRadius(const FVector& Origin, float Radius)
{
    // �� ������ ���� ��ġ�� ����
    FVector RandomUnitVector = UKismetMathLibrary::RandomUnitVector();
    float RandomDistance = FMath::FRandRange(0.0f, Radius);

    return Origin + RandomUnitVector * RandomDistance;
}

// ��� ����
void UC_TaskMonsterPatrol::ExampleUsage()
{
    FVector Origin = FVector(0.0f, 0.0f, 0.0f); // �ڱ� �ڽ��� ��ġ (��: ���� Actor�� ��ġ)
    float Radius = 100.0f; // �ݰ�
    FVector RandomVector = GetRandomVectorInRadius(Origin, Radius);
    UE_LOG(LogTemp, Log, TEXT("Random Vector in Radius: %s"), *RandomVector.ToString());
}
