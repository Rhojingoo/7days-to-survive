// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_UI_TitleUI.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_UI_TitleUI : public UUserWidget
{
	GENERATED_BODY()

public:
	//UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//FString IPAddress = TEXT("127.0.0.1"); //IP주소
	//
	//UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//FString Port = TEXT("30002"); //포트 설정 
	//
	
	UFUNCTION(BlueprintCallable)
	void ServerStart(); //서버 열기 

	//UFUNCTION(BlueprintCallable)
	//void SelectChange(FString _Text);
	//

	virtual bool Initialize() override;
};
