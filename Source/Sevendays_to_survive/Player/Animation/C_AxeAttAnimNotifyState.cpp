// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Animation/C_AxeAttAnimNotifyState.h"
#include "Player/Global/C_GlobalPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Monster/C_ZombieBase.h"
#include "Map/C_ItemSourceHISMA.h"

void UC_AxeAttAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AC_GlobalPlayer* PlayCharacter = MeshComp->GetOwner<AC_GlobalPlayer>();

	
	if (nullptr == PlayCharacter)
	{
		return;
	}

	if (UGameplayStatics::GetGameMode(MeshComp->GetWorld()) == nullptr)
	{
		return;
	}

	FHitResult Hit;

	UStaticMeshComponent* ItemMesh=PlayCharacter->GetStaticItemMesh()[1];

	FTransform ItemTansForm = ItemMesh->GetSocketTransform(FName("AttackPoint"));
	//FVector ItemLocation = ItemMesh->GetSocketLocation(FName("AttackPoint"));
	
	//FTransform ItemTansForm=ItemMesh->GetRelativeTransform();
	FVector ItemRelativeLocationAdd=ItemMesh->GetRelativeLocation()+FVector(20.0f,20.0f,20.0f);

	FVector Start= ItemMesh->GetSocketLocation(FName("AttackPoint"));
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
		AC_ZombieBase* Zombie = Cast<AC_ZombieBase>(ActorHit);

		if (Zombie)
		{
			//ZombieDieTrace(Zombie);
			Zombie->SetRagDoll();
			FTimerHandle ZombieDestory;

			MeshComp->GetWorld()->GetTimerManager().SetTimer(ZombieDestory, FTimerDelegate::CreateLambda([=]()
			{
				if (Zombie != nullptr)
				{
					Zombie->Destroy();
				}
				//GetWorld()->GetTimerManager().ClearTimer(ZombieDestory);
			}), 5.0f, false);

		}

		AC_ItemSourceHISMA* MapObject = Cast<AC_ItemSourceHISMA>(ActorHit);
		
		if (MapObject)
		{
			int ItemHit = Hit.Item;
			MapObject->Damage(ItemHit, 10, PlayCharacter);
		}

		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *(ActorHit->GetName())));
	}

}

void UC_AxeAttAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UC_AxeAttAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
