// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_Car.h"

#include "Map/UI/C_MapInteractionWidget.h"

// Sets default values
AC_Car::AC_Car()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	SetRootComponent(StaticMeshComponent);

	MapInteractionWidgetComponent->SetupAttachment(StaticMeshComponent);
}

// Called when the game starts or when spawned
void AC_Car::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AC_Car::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Car::MapInteract()
{
	// TODO: Open Storage UI
}

void AC_Car::ShowInteractionWidget()
{
	Super::ShowInteractionWidget();

	FVector Location = GetActorLocation() + MessageRelativeLocation;
	MapInteractionWidgetComponent->SetWorldLocation(Location);

	FString Text = TEXT("Open trunk");
	MapInteractionWidget->SetMessage(Text);
}

void AC_Car::HideInteractionWidget()
{
	Super::HideInteractionWidget();
}

