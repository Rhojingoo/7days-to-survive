// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Animation/C_SwdAndBatAttAnimNotifyState.h"
#include "Player/Global/C_GlobalPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Monster/C_ZombieBase.h"
#include "Map/C_ItemSourceHISMA.h"
#include "Player/Global/C_PlayerEnum.h"

void UC_SwdAndBatAttAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AC_GlobalPlayer* PlayCharacter = MeshComp->GetOwner<AC_GlobalPlayer>();


	if (nullptr == PlayCharacter)
	{
		return;
	}

	float Damage = 0.0f;

	switch (PlayCharacter->GetPlayerCurState())
	{
	case EWeaponUseState::Sword:
		Damage = 50.0f;
		break;
	case EWeaponUseState::bat:
		Damage = 20.0f;
	default:
		break;
	}

	PlayCharacter->AttCalstamina();
	if (UGameplayStatics::GetGameMode(MeshComp->GetWorld()) == nullptr)
	{
		return;
	}

	FHitResult Hit;

	UStaticMeshComponent* ItemMesh = PlayCharacter->GetStaticItemMesh()[static_cast<int>(EStaticItemSlot::RSword)];

	FTransform ItemTansForm = ItemMesh->GetSocketTransform(FName("RSword"));
	//FVector ItemLocation = ItemMesh->GetSocketLocation(FName("AttackPoint"));

	//FTransform ItemTansForm=ItemMesh->GetRelativeTransform();
	FVector ItemRelativeLocationAdd = ItemMesh->GetRelativeLocation() + FVector(40.0f, 20.0f, 20.0f);

	FVector Start = ItemMesh->GetSocketLocation(FName("RSword"));
	FVector End = UKismetMathLibrary::TransformLocation(ItemTansForm, ItemRelativeLocationAdd);
	//LineTraceSingle(CurWeapon, Start, End, ETraceTypeQuery::TraceTypeQuery1, false, Actors, EDrawDebugTrace::ForDuration, Hit, true, FLinearColor::Red, FLinearColor::Green, 5.0f);

	TArray<AActor*> AxeAtt;

	bool OKAtt = UKismetSystemLibrary::SphereTraceSingle(ItemMesh, Start, End, 30.0f, ETraceTypeQuery::TraceTypeQuery1, false, AxeAtt, EDrawDebugTrace::ForDuration, Hit, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
	//FVector Start;

	if (false == OKAtt)
	{
		return;
	}

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UGameplayStatics::ApplyDamage(ActorHit, 10.0f, nullptr, PlayCharacter, nullptr);
		{
			AC_ZombieBase* Zombie = Cast<AC_ZombieBase>(ActorHit);

			if (Zombie)
			{
				//ZombieDieTrace(Zombie);
				if (PlayCharacter->GetPlayerCurState() == EWeaponUseState::bat)
				{
					PlayCharacter->WeaponSwingSound(Hit, false);
				}
				else
				{
					PlayCharacter->WeaponSwingSound(Hit, true);
					PlayCharacter->CreateZombieBlood(Hit);
				}
				Zombie->SetHP(Damage);


				/*FTimerHandle ZombieDestory;

				MeshComp->GetWorld()->GetTimerManager().SetTimer(ZombieDestory, FTimerDelegate::CreateLambda([=]()
				{
					if (Zombie != nullptr)
					{
						Zombie->Destroy();
					}
				}), 5.0f, false);*/

			}
		}

		{
			AC_ItemSourceHISMA* MapObject = Cast<AC_ItemSourceHISMA>(ActorHit);

			if (MapObject)
			{
				int ItemHit = Hit.Item;
				PlayCharacter->WeaponSwingSound(Hit, false);
				MapObject->Damage(ItemHit, 20, PlayCharacter);

			}
		}
	}
}

void UC_SwdAndBatAttAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UC_SwdAndBatAttAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
