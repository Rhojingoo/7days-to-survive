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
	


		if (nullptr == Inst)
		{
			return;
		}

		Inst->TitleToGameInfo.ServerOpenCheck = true;
		Inst->TitleToGameInfo.UserIp = "192.168.0.117"; //값을 계속 수동으로 변경해줘야합니다. 아직은
		Inst->TitleToGameInfo.ServerPort = "30002"; //포트 값을 가져와야한다.
		
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("7Days_Map")); //메인 게임플레이장소
		//UGameplayStatics::OpenLevel(GetWorld(), TEXT("testChartestLevel")); //임시로 열어둠 
	//서버 오픈 끝




}

void UC_UserWidget_Server::LoginDataInit(UDataTable* _LoginData)
{

	TArray<FC_UITableRow*> arr;
	_LoginData->GetAllRows<FC_UITableRow>(TEXT("GetAllRows"), arr);

	if (true == arr.IsEmpty())
	{
		return;
	}


	for (size_t i = 0; i < arr.Num(); i++)
	{
		FC_UITableRow* Data = arr[i];
		Data->UserName;
		Data->UserIp;
		FString Option = FString::Printf(TEXT("[%s][%s]"), *Data->UserName, *Data->UserIp);
		
	}

}




bool UC_UserWidget_Server::Initialize()
{
	bool ReturnValue = Super::Initialize();

	IPAddress = TEXT("127.0.0.1");

	return ReturnValue;
}



void UC_UserWidget_Server::ServerConnect(FString _Ip )
{
	UC_STSInstance* Inst = GetGameInstance<UC_STSInstance>();


	Inst->TitleToGameInfo.UserIp = _Ip;
	Inst->TitleToGameInfo.ServerPort = Port;

	FString IpAddress = _Ip;
	
	
	TMap<FString, FStringFormatArg> Args;
	Args.Emplace(TEXT("0"), IpAddress); 
	Args.Emplace(TEXT("1"), Port);
	FString ConnectLevel = FString::Format(TEXT("{0}:{1}"), Args);
	
	UGameplayStatics::OpenLevel(GetWorld(), *ConnectLevel);



}



void UC_UserWidget_Server::SelectChange(FString _Text)
{
	_Text.RemoveAt(0);
	_Text.RemoveAt(_Text.Len() - 1);


	FString Name;
	FString IP;
	_Text.Split(TEXT("]["), &Name, &IP);

	IPAddress = IP;



}