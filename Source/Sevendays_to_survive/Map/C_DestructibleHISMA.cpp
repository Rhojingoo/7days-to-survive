// Fill out your copyright notice in the Description page of Project Settings.

#include "Map/C_DestructibleHISMA.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AC_DestructibleHISMA::AC_DestructibleHISMA()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HISM = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HierarchicalInstancedStaticMesh"));
	SetRootComponent(HISM);
}

// Called when the game starts or when spawned
void AC_DestructibleHISMA::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_DestructibleHISMA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_DestructibleHISMA::DestroyInstance_Implementation(int _Index)
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Call HISMA::DestroyInstance"));

	bool Result = HISM->RemoveInstance(_Index);

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

