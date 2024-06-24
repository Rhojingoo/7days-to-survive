// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_ItemSourceHISMA.h"
#include "Kismet/KismetSystemLibrary.h"

void AC_ItemSourceHISMA::SetData(FC_ItemSourceTableRow& _Data)
{
	Data = _Data;
}

void AC_ItemSourceHISMA::Damage_Implementation(int _Index, int _Damage)
{
	Super::Damage_Implementation(_Index, _Damage);

	for (auto& DropItem : Data.DropItems)
	{
		UEnum* Enum = StaticEnum<EItemType>();
		FString EnumName = Enum->GetNameStringByValue(static_cast<int>(DropItem.Key));
		FString Message = FString::Printf(TEXT("you've got %d %ss."), DropItem.Value, *EnumName);
		UKismetSystemLibrary::PrintString(GetWorld(), Message);
	}
	
}
