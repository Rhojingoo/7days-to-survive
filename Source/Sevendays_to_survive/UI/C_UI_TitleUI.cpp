// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_UI_TitleUI.h"
#include "Kismet/GameplayStatics.h"
void UC_UI_TitleUI::ServerStart()
{
	// 게임 인스턴스가 필요함 

}

bool UC_UI_TitleUI::Initialize()
{
	bool ReturnValue = Super::Initialize(); //
	//IPAddress = TEXT("127.0.0.1");
	return ReturnValue;

	
}

//void UC_UI_TitleUI::SelectChange(FString _Text)
//{
//	//데이터 테이블 미적용
//	
//	
//	//IPAddress = _Text;
//	
//}

