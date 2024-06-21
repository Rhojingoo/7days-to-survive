// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STS/C_STSInstance.h" //��ӹ޾Ƽ� ��� 
#include"UI/C_UITableRow.h"
#include "C_UserWidget_Server.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_UserWidget_Server : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void StringTODataTable(FString _Name,FString _UserIP);

private:
	
};
