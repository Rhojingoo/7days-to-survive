// Fill out your copyright notice in the Description page of Project Settings.


#include "STSBlueprintFunctionLibrary.h"
#include "IDesktopPlatform.h"
#include "DesktopPlatformModule.h"

 void USTSBlueprintFunctionLibrary::GetAllFileName()
{
	 IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	 FString DefaultFile = TEXT("");
	 FString DefaultPath = FPaths::ProjectSavedDir();
	 FString dir = FPaths::ProjectSavedDir();
	 FString Result;

	 if (DesktopPlatform) {
		 DesktopPlatform->OpenDirectoryDialog(
			 NULL,
			 TEXT("Select Directory"),	// 탐색기 제목
			 DefaultPath,	// 열고싶은 탐색기 경로
			 Result	// 선택한 디렉토리 경로가 여기에 들어옴
		 );
	 }

	 FString fileExt = TEXT("*");

	 TArray<FString> FoundFileName;

	 IFileManager::Get().FindFiles(FoundFileName, *Result, *fileExt);

}