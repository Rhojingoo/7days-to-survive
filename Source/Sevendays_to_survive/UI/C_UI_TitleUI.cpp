// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_UI_TitleUI.h"
#include "Kismet/GameplayStatics.h"
#include "STS/C_STSInstance.h"


void UC_UI_TitleUI::SelectChange(FString _Text)
{
	_Text.RemoveAt(0);
	_Text.RemoveAt(_Text.Len() - 1);

	// _Text.ParseIntoArray()
	FString Name;
	FString IP;
	_Text.Split(TEXT("]["), &Name, &IP);

	IPAddress = IP;
}