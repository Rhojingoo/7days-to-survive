// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
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



//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// 에디터에서 사용하기 위해서 해주는 프로퍼  
	//bool UIOn = false;
	// 내가 사용할 데이터 테이블 

//제꺼