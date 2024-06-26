// Fill out your copyright notice in the Description page of Project Settings.

#include "Map/C_MapInteractionComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Map/C_ItemSourceHISMA.h"
#include "Player/Global/C_MapPlayer.h"
#include "STS/C_STSMacros.h"

UC_MapInteractionComponent::UC_MapInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UC_MapInteractionComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UC_MapInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UC_MapInteractionComponent::DamageItemSource(AC_ItemSourceHISMA* _ItemSource, int _Index, int _Damage)
{
	_ItemSource->Damage(_Index, _Damage);

	AC_MapPlayer* HitCharacter = Cast<AC_MapPlayer>(GetOwner());
	if (nullptr == HitCharacter)
	{
		STS_FATAL("[%s] HitCharacter is NULL.", __FUNCTION__);
	}

	_ItemSource->GainDropItems(HitCharacter);


	//APlayerController* LocalPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//if (true == IsServer())
	//{
	//	STS_LOG("Multicast_DamageItemSource", 0);
	//	Multicast_DamageItemSource(LocalPlayerController, _ItemSource,_Index, _Damage);
	//}
	//else
	//{
	//	// 클라: 서버에게 나무 HP를 깎아달라고 부탁한다.
	//	STS_LOG("Server_DamageItemSource", 0);
	//	Server_DamageItemSource(LocalPlayerController, _ItemSource, _Index, _Damage);
	//}
}

void UC_MapInteractionComponent::Server_DamageItemSource_Implementation(APlayerController* _CallingController, AC_ItemSourceHISMA* _ItemSource, int _Index, int _Damage)
{
	_ItemSource->Damage(_Index, _Damage);
	Multicast_DamageItemSource(_CallingController, _ItemSource, _Index, _Damage);
}

void UC_MapInteractionComponent::Multicast_DamageItemSource_Implementation(APlayerController* _CallingController, AC_ItemSourceHISMA* _ItemSource, int _Index, int _Damage)
{
	// 서버는 멀티캐스트에서 제외한다.
	if (true == IsServer())
	{
		return;
	}

	// 멀티캐스트를 야기한 플레이어는 멀티캐스트에서 제외한다.
	if (true == IsValid(_CallingController) && true == _CallingController->IsLocalController())
	{
		return;
	}

	_ItemSource->Damage(_Index, _Damage);
}

bool UC_MapInteractionComponent::IsServer()
{
	return UKismetSystemLibrary::IsServer(GetWorld());
}
