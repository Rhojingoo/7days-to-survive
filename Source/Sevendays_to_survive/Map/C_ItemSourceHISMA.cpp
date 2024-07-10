// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_ItemSourceHISMA.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "STS/C_STSInstance.h"
#include "Map/C_MapDataAsset.h"
#include "Map/C_ItemSourceTableRow.h"
#include "Map/C_Items.h"
#include "Player/Global/C_MapPlayer.h"
#include "Inventory/C_InventoryComponent.h"
#include "STS/C_STSMacros.h"
#include "UI/C_HealthBar.h"

AC_ItemSourceHISMA::AC_ItemSourceHISMA()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    HISMComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HierarchicalInstancedStaticMesh"));
    SetRootComponent(HISMComponent);

    HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
    HpBar->SetupAttachment(HISMComponent);
}

void AC_ItemSourceHISMA::BeginPlay()
{
    Super::BeginPlay();

    AActor* GameMode = UGameplayStatics::GetGameMode(GetWorld());
    SetOwner(GameMode);

    HpBarWidget = Cast<UC_HealthBar>(HpBar->GetWidget());

    if (nullptr == HpBarWidget)
    {
        STS_FATAL("[%s] HpBarWidget is NULL.", __FUNCTION__);
    }

    HideHpBar();

    if (true == Id.IsNone())
    {
        return;
    }

    UC_STSInstance* Inst = GetWorld()->GetGameInstanceChecked<UC_STSInstance>();
    UC_MapDataAsset* MapDataAsset = Inst->GetMapDataAsset();

    DropItems = MapDataAsset->GetItemSourceDropItems(Id);

    int MaxHp = MapDataAsset->GetItemSourceMaxHp(Id);
    int InstCount = HISMComponent->GetInstanceCount();
    for (int i = 0; i < InstCount; ++i)
    {
        MaxHpMap.Emplace(i, MaxHp);
        HpMap.Emplace(i, MaxHp);
    }

    HpBarWidget->SetMaxHealth(MaxHp);
}

void AC_ItemSourceHISMA::Tick(float _DeltaSeconds)
{
    Super::Tick(_DeltaSeconds);
}

void AC_ItemSourceHISMA::Damage_Implementation(int _Index, int _Damage, AActor* _HitActor)
{
    if (true == Id.IsNone())
    {
        return;
    }

    HpMap[_Index] -= _Damage;
    STS_LOG("[%s:%d] damaged by % d", *GetName(), _Index, _Damage);
    STS_LOG("[%s:%d] HP: %d/%d", *GetName(), _Index, HpMap[_Index], MaxHpMap[_Index]);

    // 아이템 획득
    AC_MapPlayer* ItemGainer = Cast<AC_MapPlayer>(_HitActor);
    if (nullptr != ItemGainer)
    {
        GainDropItems(ItemGainer);
    }

    if (HpMap[_Index] <= 0)
    {
        bool Result = HISMComponent->RemoveInstance(_Index);

        if (false == Result)
        {
            STS_FATAL("[%s:%d] destroy failed.", *GetName(), _Index);
        }
        else
        {
            HideHpBar();
            STS_LOG("[%s:%d] destroyed successfully.", *GetName(), _Index);
        }

        return;
    }

    // 위젯 업데이트
    if (true == HpBar->IsActive() && _Index == HpBarTargetIndex)
    {
        HpBarWidget->SetCurHealth(HpMap[HpBarTargetIndex]);
        HpBarWidget->SetMaxHealth(MaxHpMap[HpBarTargetIndex]);
    }
}

void AC_ItemSourceHISMA::GainDropItems(AC_MapPlayer* _HitCharacter)
{
    UC_InventoryComponent* InventoryComponent = _HitCharacter->GetComponentByClass<UC_InventoryComponent>();
    if (nullptr == InventoryComponent)
    {
        STS_FATAL("[%s] InventoryComponent is NULL.", __FUNCTION__);
    }

    for (FC_ItemAndCount& DropItem : DropItems)
    {
        InventoryComponent->AddItem(DropItem.Item, DropItem.Count);
        STS_LOG("got %d %ss.", DropItem.Count, *DropItem.Item->Name);
    }
}

void AC_ItemSourceHISMA::UpdateHpBar(int _Index)
{
    if (true == Id.IsNone())
    {
        return;
    }

    if (_Index < 0 || _Index >= HpMap.Num())
    {
        STS_LOG("UpdateHpBar failed. Given Index %d is out of range.", _Index);
        return;
    }

    if (HpMap[_Index] <= 0)
    {
        STS_LOG("UpdateHpBar failed. Given instance(%d) is already destroyed.", _Index);
        return;
    }

    if (false == HpBarWidget->IsVisible())
    {
        HpBarWidget->SetVisibility(ESlateVisibility::Visible);
    }

    HpBarTargetIndex = _Index;

    HISMComponent->GetInstanceTransform(_Index, HpBarTransform, true);
    FVector InstLocation = HpBarTransform.GetLocation() + FVector::UpVector * HpBarHeight;
    FVector DrawLocation = InstLocation;

    // HpBar 갱신
    HpBar->SetWorldLocation(DrawLocation);
    HpBarWidget->SetCurHealth(HpMap[HpBarTargetIndex]);
    HpBarWidget->SetMaxHealth(MaxHpMap[HpBarTargetIndex]);
}

void AC_ItemSourceHISMA::HideHpBar()
{
    HpBarWidget->SetVisibility(ESlateVisibility::Hidden);
}
