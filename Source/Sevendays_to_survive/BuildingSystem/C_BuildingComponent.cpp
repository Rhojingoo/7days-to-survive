// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSystem/C_BuildingComponent.h"
#include "BuildingSystem/C_BuildingPreview.h"
#include "BuildingSystem/C_BuildingPart.h"
#include "BuildingSystem/C_BuildingPartInterface.h"
#include "BuildingSystem/C_BuildingPartTableRow.h"
#include "BuildingSystem/C_BuildingPart.h"
#include "Landscape.h"
#include "STS/C_STSInstance.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
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
	PreviewActor->SetOwner(GetOwner());
	SetPreviewMesh(nullptr);

	AC_NickMainPlayer* PC = GetOwner<AC_NickMainPlayer>();
	CameraComponent = PC->GetComponentByClass<UCameraComponent>();

	int a = 0;
}

void UC_BuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (false == BuildMode)
	{
		return;
	}

	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> OutHits;

	FVector TraceStart = GetLineTraceStartPoint();
	FVector TraceEnd = GetLineTraceEndPoint();

	bool IsLineTraceHit = UKismetSystemLibrary::LineTraceMulti(
		GetWorld(),
		TraceStart,
		TraceEnd,
		BuildPartData[BuildPartIndex].TraceType,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		OutHits,
		true
	);

	// 레이가 적중하지 않은 경우
	if (false == IsLineTraceHit)
	{
		BuildTransform.SetLocation(TraceEnd);
		SetCanBuild(false);
		RefreshPreviewTransform();
		return;
	}

	// 레이가 소켓에 적중한 경우에 대한 처리
	for (FHitResult& OutHit : OutHits)
	{
		AActor* HitActor = OutHit.GetActor();

		if (false == HitActor->Implements<UC_BuildingPartInterface>())
		{
			continue;
		}

		BuildTransform = OutHit.GetComponent()->GetComponentTransform();
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

		return;
	}
	
	// 레이가 적중한 경우에 대한 처리
	bool IsLandscapeHit = false;
	FHitResult* OutHit = nullptr;
	for (FHitResult& Hit : OutHits)
	{
		if (true == Hit.GetActor()->IsA<ALandscape>())
		{
			IsLandscapeHit = true;
			OutHit = &Hit;
			break;
		}
	}

	if (true == IsLandscapeHit)
	{
		// 그라운드 업 처리
		FVector Location = GetLocationOnTerrain(OutHit->ImpactPoint, OutHit->Normal);
		BuildTransform.SetLocation(Location);
		RefreshPreviewTransform();

		// 충돌면의 경사가 급하면 설치할 수 없다.
		if (false == CheckBuildAngle(OutHit->Normal))
		{
			SetCanBuild(false);
			return;
		}
	}
	else
	{
		OutHit = &OutHits[0];
		BuildTransform.SetLocation(OutHit->ImpactPoint);
	}

	// 랜드스케이프를 제외한 액터와 충돌이 있는 경우
	if (true == HasPreviewCollision())
	{
		SetCanBuild(false);
	}
	// 랜드스케이프를 제외한 액터와 충돌이 없는 경우
	else
	{
		SetCanBuild(true);
	}
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
	TArray<UPrimitiveComponent*> OverlappingComponents;
	PreviewActor->GetStaticMeshComponent()->GetOverlappingComponents(OverlappingComponents);

	for (UPrimitiveComponent* OverlappingComponent : OverlappingComponents)
	{
		AActor* OverlappingActor = OverlappingComponent->GetOwner();
			
		if (true == OverlappingActor->IsA<ALandscape>())
		{
			continue;
		}

		if (true == OverlappingActor->IsA<AC_BuildingPart>() 
			&& !OverlappingComponent->ComponentHasTag(TEXT("Body")))
		{
			continue;
		}

		return true;
	}

	return false;
}
