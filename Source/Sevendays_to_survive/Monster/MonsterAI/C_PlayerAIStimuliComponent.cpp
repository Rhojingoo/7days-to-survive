// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/C_PlayerAIStimuliComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"



void UC_PlayerAIStimuliComponent::BeginPlay()
{
    Super::BeginPlay();
    RegisterForSense(TSubclassOf<UAISense>(UAISense_Sight::StaticClass()));
    RegisterForSense(TSubclassOf<UAISense>(UAISense_Hearing::StaticClass()));
    RegisterForSense(TSubclassOf<UAISense_Sight>());


    RegisterWithPerceptionSystem();
}
