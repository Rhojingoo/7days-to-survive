#pragma once

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

/**
* Display 모드로 UE_LOG를 띄웁니다. 접속자 이름을 표시합니다.
* [주의] 가변 인자를 사용할 필요가 없더라도 아무 값이나 넣어줘야 합니다.
* [예시] STS_LOG("ItemName: %s, ItemCount: %d", *ItemName, ItemCount);
* [예시] STS_LOG("Item Added", 0);
*/
#define STS_LOG(Format, ...) {\
	APlayerController* PC_Unshadowing2357 = UGameplayStatics::GetPlayerController(GetWorld(), 0);\
	UPlayer* Player_Unshadowing2357 = PC_Unshadowing2357->GetNetOwningPlayer();\
	UE_LOG(LogTemp, Display, TEXT("%s> " TEXT(Format)), *Player_Unshadowing2357->GetName(), __VA_ARGS__);\
}

/**
* Error 모드로 UE_LOG를 띄웁니다. 접속자 이름을 표시합니다.
* [주의] 가변 인자를 사용할 필요가 없더라도 아무 값이나 넣어줘야 합니다.
* [예시] STS_ERROR("ItemName: %s, ItemCount: %d", *ItemName, ItemCount);
* [예시] STS_ERROR("Item Added", 0);
*/
#define STS_ERROR(Format, ...) {\
	APlayerController* PC_Unshadowing2357 = UGameplayStatics::GetPlayerController(GetWorld(), 0);\
	UPlayer* Player_Unshadowing2357 = PC_Unshadowing2357->GetNetOwningPlayer();\
	UE_LOG(LogTemp, Error, TEXT("%s> " TEXT(Format)), *Player_Unshadowing2357->GetName(), __VA_ARGS__);\
}

/**
* Fatal 모드로 UE_LOG를 띄웁니다. 접속자 이름을 표시합니다.
* [주의] 가변 인자를 사용할 필요가 없더라도 아무 값이나 넣어줘야 합니다.
* [예시] STS_FATAL("ItemName: %s, ItemCount: %d", *ItemName, ItemCount);
* [예시] STS_FATAL("Item Added", 0);
*/
#define STS_FATAL(Format, ...) {\
	APlayerController* PC_Unshadowing2357 = UGameplayStatics::GetPlayerController(GetWorld(), 0);\
	UPlayer* Player_Unshadowing2357 = PC_Unshadowing2357->GetNetOwningPlayer();\
	UE_LOG(LogTemp, Fatal, TEXT("%s> " TEXT(Format)), *Player_Unshadowing2357->GetName(), __VA_ARGS__);\
}

/**
* 화면에 String을 띄웁니다. 접속자 이름을 표시합니다.
* [주의] 가변 인자를 사용할 필요가 없더라도 아무 값이나 넣어줘야 합니다.
* [예시] STS_PRINTSTRING("ItemName: %s, ItemCount: %d", *ItemName, ItemCount);
* [예시] STS_PRINTSTRING("Item Added", 0);
*/
#define STS_PRINTSTRING(Format, ...) {\
	APlayerController* PC_Unshadowing2357 = UGameplayStatics::GetPlayerController(GetWorld(), 0);\
	UPlayer* Player_Unshadowing2357 = PC_Unshadowing2357->GetNetOwningPlayer();\
	FString Message = FString::Printf(TEXT("%s> " TEXT(Format)), *Player_Unshadowing2357->GetName(), __VA_ARGS__);\
	UKismetSystemLibrary::PrintString(GetWorld(), Message);\
}