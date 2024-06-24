// Fill out your copyright notice in the Description page of Project Settings.

#include "Map/C_DestructibleHISMA.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AC_DestructibleHISMA::AC_DestructibleHISMA()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HISMComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HierarchicalInstancedStaticMesh"));
	SetRootComponent(HISMComponent);
}

// Called when the game starts or when spawned
void AC_DestructibleHISMA::BeginPlay()
{
	Super::BeginPlay();
	
	int InstCount = HISMComponent->GetInstanceCount();
	for (int i = 0; i < InstCount; ++i)
	{
		HpMap.Emplace(i, 100);
	}
}

void AC_DestructibleHISMA::Damage_Implementation(int _Index, int _Damage)
{
	HpMap[_Index] -= _Damage;
	
	FString Name = GetName();
	FString Message = FString::Printf(TEXT("%s's %d instance damaged %d"), *Name, _Index, _Damage);
	UKismetSystemLibrary::PrintString(GetWorld(), Message);
}

// Called every frame
void AC_DestructibleHISMA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_DestructibleHISMA::DestroyInstance_Implementation(int _Index)
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Call HISMA::DestroyInstance"));

	bool Result = HISMComponent->RemoveInstance(_Index);

	FString Message;
	
	if (false == Result)
	{
		Message = TEXT("Remove Failed");
	}
	else
	{
		Message = FString::Format(TEXT("Remove Success. Index = {0}"), { _Index });
	}

	UKismetSystemLibrary::PrintString(GetWorld(), Message);
}

