#pragma once

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

/**
* Display ���� UE_LOG�� ���ϴ�. ������ �̸��� ǥ���մϴ�.
* [����] ���� ���ڸ� ����� �ʿ䰡 ������ �ƹ� ���̳� �־���� �մϴ�.
* [����] STS_LOG("ItemName: %s, ItemCount: %d", *ItemName, ItemCount);
* [����] STS_LOG("Item Added", 0);
*/
#define STS_LOG(Format, ...) {\
	APlayerController* PC_Unshadowing2357 = UGameplayStatics::GetPlayerController(GetWorld(), 0);\
	UPlayer* Player_Unshadowing2357 = PC_Unshadowing2357->GetNetOwningPlayer();\
	UE_LOG(LogTemp, Display, TEXT("%s> " TEXT(Format)), *Player_Unshadowing2357->GetName(), __VA_ARGS__);\
}

/**
* Error ���� UE_LOG�� ���ϴ�. ������ �̸��� ǥ���մϴ�.
* [����] ���� ���ڸ� ����� �ʿ䰡 ������ �ƹ� ���̳� �־���� �մϴ�.
* [����] STS_ERROR("ItemName: %s, ItemCount: %d", *ItemName, ItemCount);
* [����] STS_ERROR("Item Added", 0);
*/
#define STS_ERROR(Format, ...) {\
	APlayerController* PC_Unshadowing2357 = UGameplayStatics::GetPlayerController(GetWorld(), 0);\
	UPlayer* Player_Unshadowing2357 = PC_Unshadowing2357->GetNetOwningPlayer();\
	UE_LOG(LogTemp, Error, TEXT("%s> " TEXT(Format)), *Player_Unshadowing2357->GetName(), __VA_ARGS__);\
}

/**
* Fatal ���� UE_LOG�� ���ϴ�. ������ �̸��� ǥ���մϴ�.
* [����] ���� ���ڸ� ����� �ʿ䰡 ������ �ƹ� ���̳� �־���� �մϴ�.
* [����] STS_FATAL("ItemName: %s, ItemCount: %d", *ItemName, ItemCount);
* [����] STS_FATAL("Item Added", 0);
*/
#define STS_FATAL(Format, ...) {\
	APlayerController* PC_Unshadowing2357 = UGameplayStatics::GetPlayerController(GetWorld(), 0);\
	UPlayer* Player_Unshadowing2357 = PC_Unshadowing2357->GetNetOwningPlayer();\
	UE_LOG(LogTemp, Fatal, TEXT("%s> " TEXT(Format)), *Player_Unshadowing2357->GetName(), __VA_ARGS__);\
}

/**
* ȭ�鿡 String�� ���ϴ�. ������ �̸��� ǥ���մϴ�.
* [����] ���� ���ڸ� ����� �ʿ䰡 ������ �ƹ� ���̳� �־���� �մϴ�.
* [����] STS_PRINTSTRING("ItemName: %s, ItemCount: %d", *ItemName, ItemCount);
* [����] STS_PRINTSTRING("Item Added", 0);
*/
#define STS_PRINTSTRING(Format, ...) {\
	APlayerController* PC_Unshadowing2357 = UGameplayStatics::GetPlayerController(GetWorld(), 0);\
	UPlayer* Player_Unshadowing2357 = PC_Unshadowing2357->GetNetOwningPlayer();\
	FString Message = FString::Printf(TEXT("%s> " TEXT(Format)), *Player_Unshadowing2357->GetName(), __VA_ARGS__);\
	UKismetSystemLibrary::PrintString(GetWorld(), Message);\
}