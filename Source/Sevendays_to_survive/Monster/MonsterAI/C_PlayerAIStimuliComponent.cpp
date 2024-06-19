// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAI/C_PlayerAIStimuliComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"



bool UC_PlayerAIStimuliComponent::Init()
{
    RegisterForSense(TSubclassOf<UAISense>(UAISense_Sight::StaticClass()));
    RegisterForSense(TSubclassOf<UAISense>(UAISense_Hearing::StaticClass()));
    RegisterWithPerceptionSystem();
    return false;
}
