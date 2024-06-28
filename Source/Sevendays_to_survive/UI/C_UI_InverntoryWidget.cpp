// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_UI_InverntoryWidget.h"

#include "Player/Global/C_MapPlayer.h"


void UC_UI_InverntoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	APlayerController* Test = GetOwningPlayer();


	AC_MapPlayer* MapPlayer = Cast<AC_MapPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	//WidgetInventory = MapPlayer->GetmapInventory();
	
	WidgetInventory->GetItemAndCount(0, 0);

	
	

}