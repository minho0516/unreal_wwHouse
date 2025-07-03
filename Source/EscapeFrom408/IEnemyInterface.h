#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IEnemyInterface.generated.h"

// 이건 UINTERFACE, 구현 X
UINTERFACE(MinimalAPI)
class UIEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

// 여기가 진짜 인터페이스, 함수 선언만!
class ESCAPEFROM408_API IIEnemyInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void TakeDamage(float Damage);
};