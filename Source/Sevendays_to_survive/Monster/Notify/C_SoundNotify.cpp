// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Notify/C_SoundNotify.h"
#include "STS/C_STSInstance.h"
#include "Monster/MonsterData/MonsterDataRow.h"
#include "Monster/C_ZombieBase.h"
#include "Kismet/GameplayStatics.h"

UC_SoundNotify::UC_SoundNotify()
{

}

void UC_SoundNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    AC_ZombieBase* Zombie = Cast<AC_ZombieBase>(MeshComp->GetOwner());
    if (Zombie)
    {
        UC_STSInstance* Inst = Cast<UC_STSInstance>(Zombie->GetGameInstance());
        MonsterName = Zombie->GetName();
        FMonsterDataRow* Row = Inst->GetMonsterData(*(MonsterName));

        if (Row)
        {
            uint8 MonsterState = static_cast<uint8>(Zombie->GetState());
            if (USoundWave** SoundWavePtr = Row->SoundFile.Find(MonsterState))
            {
                if (*SoundWavePtr)
                {
                    UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), *SoundWavePtr, MeshComp->GetComponentLocation());
                }
            }
            else
            {
                Super::Notify(MeshComp, Animation); // Fallback to the parent class implementation
            }
        }
    }

}