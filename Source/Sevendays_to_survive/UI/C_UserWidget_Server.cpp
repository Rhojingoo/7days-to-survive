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
		Inst->TitleToGameInfo.UserIp = "172.29.115.246";
		Inst->TitleToGameInfo.ServerPort = "30001"; //��Ʈ ���� �����;��Ѵ�.
		//�ϴ� 30001�������� ����ϰڽ��ϴ�.

		UGameplayStatics::OpenLevel(GetWorld(), TEXT("testPlayLevel")); //�ӽ÷� ����� 
	//���� ���� ��




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


	//int32 RowIndex = 0; // ������ �� �ε���
	//if (MyDataTable)
	//{
	//	TMap<FName, FString> RowMap = MyDataTable->GetRowMap(RowIndex);
	//	FString Value = RowMap["ColumnName"]; // �� �̸����� �� ��������
	//}

}