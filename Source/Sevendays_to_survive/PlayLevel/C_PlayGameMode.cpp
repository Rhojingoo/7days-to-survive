// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayLevel/C_PlayGameMode.h"
#include "STS/C_STSInstance.h"
#include "Map/C_ItemSourceHISMA.h"
#include "Map/C_ItemSourceTableRow.h"
#include "Kismet/GameplayStatics.h"

void AC_PlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	// ¸Ê ¼¼ÆÃ
	UC_STSInstance* Inst = GetWorld()->GetGameInstanceChecked<UC_STSInstance>();
	ItemSourceDataMap = Inst->GetItemSourceDataMap();

	TArray<AActor*> AllItemSources;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_ItemSourceHISMA::StaticClass(), AllItemSources);

	for (AActor* ItemSourceAsActor : AllItemSources)
	{
		AC_ItemSourceHISMA* ItemSource = Cast<AC_ItemSourceHISMA>(ItemSourceAsActor);

		UHierarchicalInstancedStaticMeshComponent* HISM = ItemSource->GetComponentByClass<UHierarchicalInstancedStaticMeshComponent>();
		UStaticMesh* MeshPtr = HISM->GetStaticMesh();
		int64 Key = reinterpret_cast<int64>(MeshPtr);

		if (false == ItemSourceDataMap.Contains(Key))
		{
			continue;
		}

		ItemSource->SetData(ItemSourceDataMap[Key]);

		int a = 0;
	}
}
