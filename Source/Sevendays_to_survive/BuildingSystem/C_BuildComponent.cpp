// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSystem/C_BuildComponent.h"
#include "BuildingSystem/BuildingPart.h"
#include "BuildingSystem/C_BuildPartTableRow.h"
#include "STS/C_STSInstance.h"
//#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UC_BuildComponent::UC_BuildComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UC_BuildComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UC_STSInstance* Inst = GetWorld()->GetGameInstanceChecked<UC_STSInstance>();
	BuildPartData = Inst->GetBuildPartData();
}


// Called every frame
void UC_BuildComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FVector UC_BuildComponent::GetLineTraceStartPoint()
{
	FVector Point = CameraComponent->K2_GetComponentLocation();
	FVector Forward = CameraComponent->GetForwardVector();
	return Point + StartPointOffset * Forward;
}

FVector UC_BuildComponent::GetLineTraceEndPoint()
{
	FVector Point = CameraComponent->K2_GetComponentLocation();
	FVector Forward = CameraComponent->GetForwardVector();
	return Point + EndPointOffset * Forward;
}

void UC_BuildComponent::FirstPreviewTick()
{
	if (false == IsFirstPreviewTick)
	{
		return;
	}
	IsFirstPreviewTick = false;

	PreviewSMComponent = Cast<UStaticMeshComponent>(GetOwner()->AddComponentByClass(UStaticMeshComponent::StaticClass(), true, BuildTransform, false));
	PreviewSMComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	PreviewSMComponent->bHiddenInGame = false;

	PreviewSMComponent->SetStaticMesh(BuildPartData[BuildPartIndex].Mesh);
	PreviewSMComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UC_BuildComponent::SetPreviewTransform(FVector _ImpactPoint, AActor* _HitActor, UPrimitiveComponent* _HitComponent, FVector _TraceEnd)
{
	if (true == IsLineTraceHit)
	{
		SetPreviewTransform_Hit(_ImpactPoint, _HitActor, _HitComponent);
	}
	else
	{
		SetPreviewTransform_NoHit(_TraceEnd);
	}
}

void UC_BuildComponent::PlaceBuildPart()
{
	if (!BuildMode || !CanBuild)
	{
		return;
	}

	TSubclassOf<AActor> ActorClass = BuildPartData[BuildPartIndex].Actor;
	
	AActor* BuildPartActor = GetWorld()->SpawnActor<AActor>(ActorClass, BuildTransform);
	BuildPartActor->SetActorEnableCollision(true);
}

void UC_BuildComponent::IncBuildPartIndex()
{
	BuildPartIndex = UKismetMathLibrary::Clamp(BuildPartIndex + 1, 0, BuildPartData.Num() - 1);

	PreviewSMComponent->SetStaticMesh(nullptr);
	IsFirstPreviewTick = true;
}

void UC_BuildComponent::DecBuildPartIndex()
{
	BuildPartIndex = UKismetMathLibrary::Clamp(BuildPartIndex - 1, 0, BuildPartData.Num() - 1);

	PreviewSMComponent->SetStaticMesh(nullptr);
	IsFirstPreviewTick = true;
}

void UC_BuildComponent::SetPreviewTransform_Hit(FVector& _ImpactPoint, AActor*& _HitActor, UPrimitiveComponent*& _HitComponent)
{
	BuildTransform.SetLocation(_ImpactPoint);
	HitActor = _HitActor;
	HitComponent = _HitComponent;

	bool FoundSocket = false;
	if (true == HitActor->Implements<UBuildingPart>())
	{
		TArray<UBoxComponent*> Sockets = IBuildingPart::Execute_GetSockets(HitActor);

		for (UBoxComponent* Socket : Sockets)
		{
			if (Socket == HitComponent)
			{
				FoundSocket = true;
				break;
			}
		}
	}

	if (true == FoundSocket)
	{
		BuildTransform = HitComponent->GetComponentTransform();
	}

	PreviewSMComponent->SetMaterial(0, GreenMaterial);
	PreviewSMComponent->SetWorldTransform(BuildTransform);

	CanBuild = true;
}

void UC_BuildComponent::SetPreviewTransform_NoHit(FVector& _TraceEnd)
{
	BuildTransform.SetLocation(_TraceEnd);
	PreviewSMComponent->SetMaterial(0, RedMaterial);
	PreviewSMComponent->SetWorldTransform(BuildTransform);

	CanBuild = false;
}