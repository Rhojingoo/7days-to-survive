// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_PickUpComponent.h"

UC_PickUpComponent::UC_PickUpComponent()
{
	SphereRadius = 32.f;
}

void UC_PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UC_PickUpComponent::OnSphereBeginOverlap);
}

void UC_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AC_NickMainPlayer* Character = Cast<AC_NickMainPlayer>(OtherActor);
	if (Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
