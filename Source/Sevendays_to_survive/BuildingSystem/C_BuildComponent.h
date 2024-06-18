// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "C_BuildComponent.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SEVENDAYS_TO_SURVIVE_API UC_BuildComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_BuildComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(Category = "Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(Category = "Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PreviewSMComponent = nullptr;

private:
	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FTransform BuildTransform;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsLineTraceHit = false;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AActor* HitActor = nullptr;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPrimitiveComponent* HitComponent = nullptr;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool FoundSocket = false;

	UPROPERTY(Category = "Variable", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FTransform SocketTransform;

private:
	UPROPERTY(Category = "Constant", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float StartPointOffset = 300.0f;

	UPROPERTY(Category = "Constant", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float EndPointOffset = 1500.0f;

	UPROPERTY(Category = "Constant", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMaterial* GreenMaterial = nullptr;

	UPROPERTY(Category = "Constant", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMaterial* RedMaterial = nullptr;

private:
	UFUNCTION(BluePrintCallable)
	FVector GetLineTraceStartPoint();

	UFUNCTION(BluePrintCallable)
	FVector GetLineTraceEndPoint();

	UFUNCTION(BluePrintCallable)
	void SetPreviewTransform(FVector _ImpactPoint, AActor* _HitActor, UPrimitiveComponent* _HitComponent, FVector _TraceEnd);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void EventDetectSockets();

private:
	// Non BP

	void SetPreviewTransform_Hit(FVector& _ImpactPoint, AActor*& _HitActor, UPrimitiveComponent*& _HitComponent);

	void SetPreviewTransform_NoHit(FVector& _TraceEnd);
};
