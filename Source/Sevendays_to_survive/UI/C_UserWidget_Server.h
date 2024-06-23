// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STS/C_STSInstance.h" //상속받아서 사용 
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

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Port;
	
	UFUNCTION(BlueprintCallable)
	void ServerOpen();

	UFUNCTION(BlueprintCallable)
	void ServerConnect(FString _Ip , FString _Port);

	UFUNCTION(BlueprintCallable)
	void SelectChange(FString _Text);

	FString IPAddress = "None";
private:
	
};
