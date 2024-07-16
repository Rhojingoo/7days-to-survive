// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSystem/C_Door.h"

AC_Door::AC_Door()
{
}

void AC_Door::MapInteract()
{
	switch (DoorState)
	{
	case EDoorState::Opened:
		Close();
		break;
	case EDoorState::Closed:
		Open();
		break;
	case EDoorState::Opening:
	case EDoorState::Closing:
		return;
	default:
		break;
	}
}

void AC_Door::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocation = GetActorLocation();
}

void AC_Door::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (EDoorState::Opening == DoorState)
	{
		Theta += 90.0f * DeltaSeconds / OpenTime;

		if (Theta >= 90.0f)
		{
			DoorState = EDoorState::Opened;
			Theta = 90.0f;
		}
	}
	else if (EDoorState::Closing == DoorState)
	{
		Theta -= 90.0f * DeltaSeconds / OpenTime;

		if (Theta <= 0.0f)
		{
			DoorState = EDoorState::Closed;
			Theta = 0.0f;
		}
	}

	double X = FMath::Cos(FMath::DegreesToRadians(Theta));
	double Y = FMath::Sin(FMath::DegreesToRadians(Theta));
	SetActorRelativeRotation(FRotator(0.0, Theta, 0.0));
	SetActorLocation(SpawnLocation + FVector(X, Y, 0.0));
}

void AC_Door::Open()
{
	DoorState = EDoorState::Opening;
	Theta = 0.0f;
}

void AC_Door::Close()
{
	DoorState = EDoorState::Closing;
	Theta = 90.0f;
}