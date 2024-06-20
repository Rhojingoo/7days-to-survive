// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "Delegates/Delegate.h"
#include "C_BuildingComponent.generated.h"

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

private:
	UPROPERTY(Category = "Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(Category = "Preview", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AC_BuildingPreview> PreviewActorClass;

	UPROPERTY(Category = "Preview", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AC_BuildingPreview* PreviewActor = nullptr;

private:
	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FTransform BuildTransform;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsLineTraceHit = false;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool CanBuild = false;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool BuildMode = false;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AActor* HitActor = nullptr;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPrimitiveComponent* HitComponent = nullptr;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int BuildPartIndex = 0;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsFirstPreviewTick = true;

protected:
	UPROPERTY(Category = "Constant", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float StartPointOffset = 300.0f;

	UPROPERTY(Category = "Constant", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float EndPointOffset = 1500.0f;

	UPROPERTY(Category = "Constant", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ACharacter* PlayerCharacter = nullptr;

	UPROPERTY(Category = "Constant", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMaterial* GreenMaterial = nullptr;

	UPROPERTY(Category = "Constant", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMaterial* RedMaterial = nullptr;

	UPROPERTY(Category = "Constant", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<struct FC_BuildingPartTableRow> BuildPartData;

private:
	UFUNCTION(BlueprintCallable)
	FVector GetLineTraceStartPoint();

	UFUNCTION(BlueprintCallable)
	FVector GetLineTraceEndPoint();

	UFUNCTION(BlueprintCallable)
	void SetPreviewTransform(FVector _ImpactPoint, AActor* _HitActor, UPrimitiveComponent* _HitComponent, FVector _TraceEnd);

	UFUNCTION(BlueprintCallable)
	void ToggleBuildMode();

	UFUNCTION(BlueprintCallable)
	void PlaceBuildPart();

	UFUNCTION(BlueprintCallable)
	void IncBuildPartIndex();

	UFUNCTION(BlueprintCallable)
	void DecBuildPartIndex();

	UFUNCTION(BlueprintCallable)
	void RotatePreview();

private:
	// Non BP Functions

	void SetPreviewTransform_Hit(FVector& _ImpactPoint, AActor*& _HitActor, UPrimitiveComponent*& _HitComponent);

	void SetPreviewTransform_NoHit(FVector& _TraceEnd);

	void SetPreviewMesh(UStaticMesh* _Mesh);

private:
	// RPC

	UFUNCTION(Server, Reliable)
	void SpawnBuildPart(TSubclassOf<AActor> _ActorClass, const FTransform& _SpawnTransform);

	void SpawnBuildPart_Implementation(TSubclassOf<AActor> _ActorClass, const FTransform& _SpawnTransform);
};
