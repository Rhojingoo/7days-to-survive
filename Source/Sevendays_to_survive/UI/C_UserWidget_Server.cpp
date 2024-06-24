// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_UserWidget_Server.h"
#include "Kismet/GameplayStatics.h"
#include "UI/C_UITableRow.h"
#include "STS/C_STSInstance.h" // �����ν��Ͻ�

void UC_UserWidget_Server::StringTODataTable(FString _Name, FString _UserIP)
{
	UC_STSInstance* UserInfo = GetWorld()->GetGameInstanceChecked<UC_STSInstance>(); //�������� 
	UserInfo->SetPlayerInfo(_Name,_UserIP);
}
void UC_UserWidget_Server::ServerOpen()
{
	UC_STSInstance* Inst = GetGameInstance<UC_STSInstance>();
	//���⼭ ������ ���̺� �����ؼ� �������°͸� �ϸ�ɵ� �ѵ� 
	// ���� IP �ּҸ� �ִ� ����� �𸣰��� 


		if (nullptr == Inst)
		{
			return;
		}

		Inst->TitleToGameInfo.ServerOpenCheck = true;
		Inst->TitleToGameInfo.UserIp = "127.0.0.1"; //���� ��� �������� ����������մϴ�. ������
		Inst->TitleToGameInfo.ServerPort = "30002"; //��Ʈ ���� �����;��Ѵ�.
		//�ϴ� 30001�������� ����ϰڽ��ϴ�.

		UGameplayStatics::OpenLevel(GetWorld(), TEXT("testPlayLevel")); //�ӽ÷� ����� 
	//���� ���� ��




}

void UC_UserWidget_Server::LoginDataInit(UDataTable* _LoginData)
{
	// std::vector
	TArray<FC_UITableRow*> arr;
	_LoginData->GetAllRows<FC_UITableRow>(TEXT("GetAllRows"), arr);

	if (true == arr.IsEmpty())
	{
		return;
	}

	// std::vector::size
	// TArray::Num
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

	IPAddress = TEXT("192.168.0.173");

	return ReturnValue;
}



void UC_UserWidget_Server::ServerConnect(FString _Ip )
{
	UC_STSInstance* Inst = GetGameInstance<UC_STSInstance>();


	Inst->TitleToGameInfo.UserIp = _Ip;
	Inst->TitleToGameInfo.ServerPort = Port;

	FString IpAddress = _Ip;
	
	FString ConnectLevel = FString::Printf(TEXT("%s:%s"), *IpAddress, *Port);
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("testPlayLevel"));
	UGameplayStatics::OpenLevel(GetWorld(), *ConnectLevel);



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


	//int32 RowIndex = 0; // ������ �� �ε���
	//if (MyDataTable)
	//{
	//	TMap<FName, FString> RowMap = MyDataTable->GetRowMap(RowIndex);
	//	FString Value = RowMap["ColumnName"]; // �� �̸����� �� ��������
	//}

}