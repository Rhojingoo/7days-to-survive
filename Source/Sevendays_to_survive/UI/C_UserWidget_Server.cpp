// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_UserWidget_Server.h"
#include "Kismet/GameplayStatics.h"
#include "UI/C_UITableRow.h"
#include "STS/C_STSInstance.h" // 게임인스턴스

void UC_UserWidget_Server::StringTODataTable(FString _Name, FString _UserIP)
{
	UC_STSInstance* UserInfo = GetWorld()->GetGameInstanceChecked<UC_STSInstance>(); //가져오기 
	UserInfo->SetPlayerInfo(_Name,_UserIP);
}
void UC_UserWidget_Server::ServerOpen()
{
	UC_STSInstance* Inst = GetGameInstance<UC_STSInstance>();
	//여기서 데이터 테이블 접근해서 가져오는것만 하면될듯 한데 
	// 서버 IP 주소를 넣는 방법을 모르겠음 


		if (nullptr == Inst)
		{
			return;
		}

		Inst->TitleToGameInfo.ServerOpenCheck = true;
		Inst->TitleToGameInfo.UserIp = "172.29.115.246";
		Inst->TitleToGameInfo.ServerPort = "30001"; //포트 값을 가져와야한다.
		//일단 30001고정으로 사용하겠습니다.

		UGameplayStatics::OpenLevel(GetWorld(), TEXT("testPlayLevel")); //임시로 열어둠 
	//서버 오픈 끝




}


void UC_UserWidget_Server::ServerConnect(FString _Ip)
{
	UC_STSInstance* Inst = GetGameInstance<UC_STSInstance>();
	FString CheckIP = Inst->TitleToGameInfo.UserIp;

}



void UC_UserWidget_Server::SelectChange(FString _Text)
{
	_Text.RemoveAt(0);
	_Text.RemoveAt(_Text.Len() - 1);

	// _Text.ParseIntoArray()
	FString Name;
	FString IP;
	_Text.Split(TEXT("]["), &Name, &IP);

	IPAddress = IP;


	//int32 RowIndex = 0; // 가져올 행 인덱스
	//if (MyDataTable)
	//{
	//	TMap<FName, FString> RowMap = MyDataTable->GetRowMap(RowIndex);
	//	FString Value = RowMap["ColumnName"]; // 열 이름으로 값 가져오기
	//}

}