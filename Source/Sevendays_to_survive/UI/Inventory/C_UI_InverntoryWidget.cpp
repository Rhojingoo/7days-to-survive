// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/C_UI_InverntoryWidget.h"

#include "Player/Global/C_MapPlayer.h"


void UC_UI_InverntoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
//	APlayerController* Test = GetOwningPlayer();


	//MapPlayer = Cast<AC_MapPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	//WidgetInventory = MapPlayer->GetmapInventory();
	
	//WidgetInventory->GetItemAndCount(0, 0); //0,0��° �������� �����´�.


}

void UC_UI_InverntoryWidget::GetDataInventory(FC_ItemAndCount _Inventory)
{
	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 20; j++)
		{
	
			UIInventory[i][j] = _Inventory;
			//������ �������� 
		}
	}
		

}
