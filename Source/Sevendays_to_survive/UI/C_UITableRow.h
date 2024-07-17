// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "UI/C_UIEnumClass.h"
#include "C_UITableRow.generated.h"

/**
 * 
 * */
 
USTRUCT(BlueprintType)
struct SEVENDAYS_TO_SURVIVE_API FC_UITableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UserName = TEXT("None");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UserIp = TEXT("None");;


	

	FString ServerPort = "None";

	bool ServerOpenCheck = false;

	
};


/**
 *
 */
USTRUCT(BlueprintType)
struct FUIWidgetDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FUIWidgetDataRow() {	}
	~FUIWidgetDataRow() {	}

public:
	// EditAnywhere 에디터에서 사용하겠다. 
	// BlueprintReadWrite 블루프린트에서 편집 가능
	// Category = "Resources"

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	bool StartOn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	EUIInputMode OpenMode = EUIInputMode::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	EUIInputMode CloseMode = EUIInputMode::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FKey Key;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FAnchorData InitScaleToPos;*/
};


