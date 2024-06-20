// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSystem/C_BuildingComponent.h"
#include "BuildingSystem/C_BuildingPreview.h"
#include "BuildingSystem/C_BuildingPart.h"
#include "BuildingSystem/C_BuildingPartInterface.h"
#include "BuildingSystem/C_BuildingPartTableRow.h"
#include "BuildingSystem/C_BuildingPart.h"
#include "STS/C_STSInstance.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"

UC_BuildingComponent::UC_BuildingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UC_BuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	UC_STSInstance* Inst = GetWorld()->GetGameInstanceChecked<UC_STSInstance>();
	BuildPartData = Inst->GetBuildPartData();

	PreviewActor = GetWorld()->SpawnActor<AC_BuildingPreview>(PreviewActorClass);
	SetPreviewMesh(nullptr);
}

void UC_BuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FVector UC_BuildingComponent::GetLineTraceStartPoint()
{
	FVector Point = CameraComponent->GetComponentLocation();
	FVector Forward = CameraComponent->GetForwardVector();
	return Point + StartPointOffset * Forward;
}

FVector UC_BuildingComponent::GetLineTraceEndPoint()
{
	FVector Point = CameraComponent->GetComponentLocation();
	FVector Forward = CameraComponent->GetForwardVector();
	return Point + EndPointOffset * Forward;
}

void UC_BuildingComponent::SetPreviewTransform(FVector _ImpactPoint, FVector _Normal, AActor* _HitActor, UPrimitiveComponent* _HitComponent, FVector _TraceEnd)
{
	if (true == IsLineTraceHit)
	{
		SetPreviewTransform_Hit(_ImpactPoint, _Normal, _HitActor, _HitComponent);
	}
	else
	{
		SetPreviewTransform_NoHit(_TraceEnd);
	}
}

void UC_BuildingComponent::ToggleBuildMode()
{
	BuildMode = !BuildMode;

	if (true == BuildMode)
	{
		SetPreviewMesh(BuildPartData[BuildPartIndex].Mesh);
	}
	else
	{
		CanBuild = false;
		SetPreviewMesh(nullptr);
	}
}

void UC_BuildingComponent::PlaceBuildPart()
{
	if (!BuildMode || !CanBuild)
	{
		return;
	}

	SpawnBuildPart(BuildPartData[BuildPartIndex].Actor, BuildTransform);
}

void UC_BuildingComponent::SpawnBuildPart_Implementation(TSubclassOf<AActor> _ActorClass, const FTransform& _SpawnTransform)
{
	AActor* BuildPartActor = GetWorld()->SpawnActor<AActor>(_ActorClass, _SpawnTransform);
	BuildPartActor->SetActorEnableCollision(true);
}

void UC_BuildingComponent::RotatePreview()
{
	FRotator NewRotator = UKismetMathLibrary::ComposeRotators(BuildTransform.Rotator(), FRotator(0.0, 5.0, 0.0));
	BuildTransform.SetRotation(UKismetMathLibrary::Conv_RotatorToQuaternion(NewRotator));
}

void UC_BuildingComponent::IncBuildPartIndex()
{
	BuildPartIndex = UKismetMathLibrary::Clamp(BuildPartIndex + 1, 0, BuildPartData.Num() - 1);
	SetPreviewMesh(BuildPartData[BuildPartIndex].Mesh);
}

void UC_BuildingComponent::DecBuildPartIndex()
{
	BuildPartIndex = UKismetMathLibrary::Clamp(BuildPartIndex - 1, 0, BuildPartData.Num() - 1);
	SetPreviewMesh(BuildPartData[BuildPartIndex].Mesh);
}

void UC_BuildingComponent::SetPreviewTransform_Hit(FVector& _ImpactPoint, FVector& _Normal, AActor*& _HitActor, UPrimitiveComponent*& _HitComponent)
{
	BuildTransform.SetLocation(_ImpactPoint);
	HitActor = _HitActor;
	HitComponent = _HitComponent;

	bool FoundSocket = false;
	if (true == HitActor->Implements<UC_BuildingPartInterface>())
	{
		TArray<UBoxComponent*> Sockets = IC_BuildingPartInterface::Execute_GetSockets(HitActor);

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
	else
	{
		FVector Location = BuildTransform.GetLocation();

		UStaticMesh* CurMesh = PreviewActor->GetStaticMeshComponent()->GetStaticMesh();
		FBoxSphereBounds Bounds = CurMesh->GetBounds();
		
		TArray<float> Coeffs;
		Coeffs.Add(UKismetMathLibrary::Abs(Bounds.BoxExtent.X / _Normal.X));
		Coeffs.Add(UKismetMathLibrary::Abs(Bounds.BoxExtent.Y / _Normal.Y));
		Coeffs.Add(UKismetMathLibrary::Abs(Bounds.BoxExtent.Z / _Normal.Z));

		int32 IndexOfMinValue = 0.0f;
		float MinValue = 0.0f;
		UKismetMathLibrary::MinOfFloatArray(Coeffs, IndexOfMinValue, MinValue);

		Location += _Normal * MinValue;
		BuildTransform.SetLocation(Location);
	}

	PreviewActor->GetStaticMeshComponent()->SetMaterial(0, GreenMaterial);
	PreviewActor->SetActorTransform(BuildTransform, true);

	CanBuild = true;
}

void UC_BuildingComponent::SetPreviewTransform_NoHit(FVector& _TraceEnd)
{
	BuildTransform.SetLocation(_TraceEnd);

	PreviewActor->GetStaticMeshComponent()->SetMaterial(0, RedMaterial);
	PreviewActor->SetActorTransform(BuildTransform);

	CanBuild = false;
}

void UC_BuildingComponent::SetPreviewMesh(UStaticMesh* _Mesh)
{
	PreviewActor->GetStaticMeshComponent()->SetStaticMesh(_Mesh);
	UStaticMesh* MeshAfterSet = PreviewActor->GetStaticMeshComponent()->GetStaticMesh();

	if (_Mesh != MeshAfterSet)
	{
		FString MeshName = "nullptr";
		if (nullptr != _Mesh)
		{
			MeshName = _Mesh->GetName();
		}
		UE_LOG(LogTemp, Fatal, TEXT("프리뷰 메시 세팅에 실패했습니다. 메시: %s"), *MeshName);
	}
}
