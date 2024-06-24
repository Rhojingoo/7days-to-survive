// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map/C_DestructibleHISMA.h"
#include "Map/C_ItemSourceTableRow.h"
#include "C_ItemSourceHISMA.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_ItemSourceHISMA : public AC_DestructibleHISMA
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetData(FC_ItemSourceTableRow& _Data);

protected:
	virtual void Damage_Implementation(int _Index, int _Damage) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta=(AllowPrivateAccess = "true"))
	FC_ItemSourceTableRow Data;
};
