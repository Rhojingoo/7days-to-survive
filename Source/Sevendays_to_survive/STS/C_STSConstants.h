
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "C_STSConstants.generated.h"

UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_STSConstants : public UObject
{
    GENERATED_BODY()

public:
    static inline FName CharacterTestLevel = TEXT("testChartestLevel");
    static inline FName RangedMonsterTestLevel = TEXT("RangedMonsterTestLevel");
};