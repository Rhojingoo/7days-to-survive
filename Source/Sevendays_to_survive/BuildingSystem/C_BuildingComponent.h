// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "Delegates/Delegate.h"
#include "C_BuildingComponent.generated.h"

class AC_BuildingPreview;
class UC_ItemBuildingPart;

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SEVENDAYS_TO_SURVIVE_API UC_BuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UC_BuildingComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintPure)
	bool IsBuilding() const;

	// 손에 건축물을 들고 있어라
	UFUNCTION(BlueprintCallable)
	void HoldBuildingPart(FName _BuildingPartId);

	UFUNCTION(BlueprintCallable)
	void PlaceBuildPart();

private:
	UPROPERTY(Category = "Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(Category = "Preview", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AC_BuildingPreview> PreviewActorClass;

	UPROPERTY(Category = "Preview", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AC_BuildingPreview* PreviewActor = nullptr;

private:
	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	const UC_ItemBuildingPart* HoldingBuildingPart = nullptr;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FTransform BuildTransform;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool CanBuild = false;

	UPROPERTY(Category = "Constant", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float StartPointOffset = 300.0f;

	UPROPERTY(Category = "Constant", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float EndPointOffset = 1500.0f;

	UPROPERTY(Category = "Constant", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMaterial* GreenMaterial = nullptr;

	UPROPERTY(Category = "Constant", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMaterial* RedMaterial = nullptr;

	UPROPERTY(Category = "Constant", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxBuildableAngle = 30.0f;

private:
	UFUNCTION(BlueprintCallable)
	FVector GetLineTraceStartPoint();

	UFUNCTION(BlueprintCallable)
	FVector GetLineTraceEndPoint();

	UFUNCTION(BlueprintCallable)
	void RotatePreview();

private:
	// Non BP Functions
	void SetCanBuild(bool _CanBuild);

	void RefreshPreviewTransform();

	FVector GetLocationOnTerrain(FVector& _Location, FVector& _Normal);

	void SetPreviewMesh(UStaticMesh* _Mesh);

	bool IsSocketHit(AActor* _HitActor, UPrimitiveComponent* _HitComponent);

	bool CheckBuildAngle(FVector& _Normal);

	bool HasPreviewCollision();
private:
	// RPC

	UFUNCTION(Server, Reliable)
	void SpawnBuildPart(TSubclassOf<AActor> _ActorClass, const FTransform& _SpawnTransform, int _MaxHp);

	void SpawnBuildPart_Implementation(TSubclassOf<AActor> _ActorClass, const FTransform& _SpawnTransform, int _MaxHp);
};
