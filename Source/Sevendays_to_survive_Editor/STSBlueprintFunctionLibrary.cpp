// Fill out your copyright notice in the Description page of Project Settings.


#include "STSBlueprintFunctionLibrary.h"
#include "IDesktopPlatform.h"
#include "DesktopPlatformModule.h"
#include "Map/C_ItemRows.h"
#include <Kismet/DataTableFunctionLibrary.h>


 void USTSBlueprintFunctionLibrary::DataTableSetting(UDataTable* DataTable)
{
	 IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	 FString DefaultFile = TEXT("");
	 FString DefaultPath = FPaths::ProjectContentDir();
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

	Result += TEXT("/*.*");

	 TArray<FString> FoundFileName;

	 IFileManager::Get().FindFiles(FoundFileName, *Result,true, true);

	 //FString fileExt = TEXT("*");

	// IFileManager::Get().FindFiles(FoundFileName, *Result, *fileExt);

	 //내가 특정한 폴더의 레퍼런스 경로가 Result인데 절대경로임 상대경로로 바꿔주는 함수있냐

	 	 if (nullptr == DataTable)
	 {
		 return;
	 }

		 // 
		 //데이터 테이블 column 얻어오기
		 TArray<FString> DataColumn = DataTable->GetColumnTitles();

		 
	 for (size_t i = 0; i < FoundFileName.Num(); i++)
	 {
		 FC_ItemRow ItemDataTable = FC_ItemRow();

		 //D:\7days-to-survive\Content\Level\TestLevel\UI\InventoryIcon\Consumable
		 ///Script/Engine.Texture2D'/Game/Level/TestLevel/UI/InventoryIcon/ConsumableIcon/blueberryPie.blueberryPie'

		 FString FinalPath = TEXT("/Script/Engine.Texture2D'/Game/Level/TestLevel/UI/InventoryIcon/ConsumableIcon/");

		 FString FileName = FoundFileName[i];

		 FileName = FileName.Replace(TEXT(".uasset"), TEXT(""));

		 FinalPath += FileName + "." + FileName + "'";

	/*	 FName Row = DataTable->GetRowStructName();
		 FString RowNames = Row.ToString();*/
		 //선택한 데이터 테이블 로우에 파일명 넣어줌

		 DataTable->AddRow(*FileName, ItemDataTable);
		 //DataTable->AddRow(*FinalPath, ItemDataTable);


		 int a = 0;
	 }

	 DataTable->Modify();
	int a = 0;
}

