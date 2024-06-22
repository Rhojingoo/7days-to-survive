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
#include "Player/MainPlayer/C_NickMainPlayer.h"

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

	AC_NickMainPlayer* PC = GetOwner<AC_NickMainPlayer>();
	CameraComponent = PC->GetComponentByClass<UCameraComponent>();

	int a = 0;
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

void UC_BuildingComponent::RefreshPreview(FVector _ImpactPoint, FVector _Normal, AActor* _HitActor, UPrimitiveComponent* _HitComponent, FVector _TraceEnd)
{
	if (false == IsLineTraceHit)
	{
		// Ray가 충돌하지 않은 경우

		BuildTransform.SetLocation(_TraceEnd);
		SetCanBuild(false);
	}
	else if (false == IsSocketHit(_HitActor, _HitComponent))
	{
		// Ray가 소켓이 아닌 액터 표면에 충돌한 경우
		if (false == CheckBuildAngle(_Normal))
		{
			// 충돌면의 경사가 급한 경우
			BuildTransform.SetLocation(_ImpactPoint);
			SetCanBuild(false);
		}
		else
		{
			// 충돌면의 경사가 완만한 경우

			if (true == HasPreviewCollision())
			{
				// 충돌이 있는 경우
				BuildTransform.SetLocation(_ImpactPoint);
				SetCanBuild(false);
			}
			else
			{
				// 충돌이 없는 경우
				FVector Location = GetLocationOnTerrain(_ImpactPoint, _Normal);
				BuildTransform.SetLocation(Location);
				SetCanBuild(true);
			}
		}
	}
	else
	{
		// Ray가 소켓에 충돌한 경우

		BuildTransform = _HitComponent->GetComponentTransform();
		RefreshPreviewTransform();

		if (true == HasPreviewCollision())
		{
			// 충돌이 있는 경우
			SetCanBuild(false);
		}
		else
		{
			// 충돌이 없는 경우
			SetCanBuild(true);
		}
	}

	RefreshPreviewTransform();
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

void UC_BuildingComponent::SetCanBuild(bool _CanBuild)
{
	CanBuild = _CanBuild;

	if (true == CanBuild)
	{
		PreviewActor->GetStaticMeshComponent()->SetMaterial(0, GreenMaterial);
	}
	else
	{
		PreviewActor->GetStaticMeshComponent()->SetMaterial(0, RedMaterial);
	}
}

void UC_BuildingComponent::RefreshPreviewTransform()
{
	PreviewActor->SetActorTransform(BuildTransform);
}

FVector UC_BuildingComponent::GetLocationOnTerrain(FVector& _Location, FVector& _Normal)
{
	UStaticMesh* CurMesh = PreviewActor->GetStaticMeshComponent()->GetStaticMesh();
	FBoxSphereBounds Bounds = CurMesh->GetBounds();

	TArray<float> Coeffs;
	Coeffs.Add(UKismetMathLibrary::Abs(Bounds.BoxExtent.X / _Normal.X));
	Coeffs.Add(UKismetMathLibrary::Abs(Bounds.BoxExtent.Y / _Normal.Y));
	Coeffs.Add(UKismetMathLibrary::Abs(Bounds.BoxExtent.Z / _Normal.Z));

	int32 IndexOfMinValue = 0.0f;
	float MinValue = 0.0f;
	UKismetMathLibrary::MinOfFloatArray(Coeffs, IndexOfMinValue, MinValue);

	FVector NewLocation = _Location + _Normal * MinValue;
	return NewLocation;
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

bool UC_BuildingComponent::IsSocketHit(AActor* _HitActor, UPrimitiveComponent* _HitComponent)
{
	bool SocketFound = false;
	if (true == _HitActor->Implements<UC_BuildingPartInterface>())
	{
		TArray<UBoxComponent*> Sockets = IC_BuildingPartInterface::Execute_GetSockets(_HitActor);

		for (UBoxComponent* Socket : Sockets)
		{
			if (Socket == _HitComponent)
			{
				SocketFound = true;
				break;
			}
		}
	}
	return SocketFound;
}

bool UC_BuildingComponent::CheckBuildAngle(FVector& _Normal)
{
	float Z = _Normal.Z;
	float Tangent = Z / UKismetMathLibrary::Sqrt(1.0f - Z * Z);
	float NormalAngle = UKismetMathLibrary::DegAtan(Tangent);
	return 90.0f - MaxBuildableAngle <= NormalAngle && NormalAngle <= 90.0f;
}

bool UC_BuildingComponent::HasPreviewCollision()
{
	TArray<AActor*> OverlappingActors;
	PreviewActor->GetStaticMeshComponent()->GetOverlappingActors(OverlappingActors);
	return !OverlappingActors.IsEmpty();
}
