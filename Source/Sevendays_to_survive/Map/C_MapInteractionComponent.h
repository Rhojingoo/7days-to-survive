// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_MapInteractionComponent.generated.h"

class AC_ItemSourceHISMA;

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SEVENDAYS_TO_SURVIVE_API UC_MapInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UC_MapInteractionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void DamageItemSource(AC_ItemSourceHISMA* _ItemSource, int _Index, int _Damage);

private:
	UFUNCTION(Server, Reliable)
	void Server_DamageItemSource(APlayerController* _CallingController, AC_ItemSourceHISMA* _ItemSource, int _Index, int _Damage);

	void Server_DamageItemSource_Implementation(APlayerController* _CallingController, AC_ItemSourceHISMA* _ItemSource, int _Index, int _Damage);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_DamageItemSource(APlayerController* _CallingController, AC_ItemSourceHISMA* _ItemSource, int _Index, int _Damage);

	void Multicast_DamageItemSource_Implementation(APlayerController* _CallingController, AC_ItemSourceHISMA* _ItemSource, int _Index, int _Damage);

	UFUNCTION(BlueprintCallable)
	bool IsServer();
};
