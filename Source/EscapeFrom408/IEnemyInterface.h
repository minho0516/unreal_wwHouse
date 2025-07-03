#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IEnemyInterface.generated.h"

// �̰� UINTERFACE, ���� X
UINTERFACE(MinimalAPI)
class UIEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

// ���Ⱑ ��¥ �������̽�, �Լ� ����!
class ESCAPEFROM408_API IIEnemyInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void TakeDamage(float Damage);
};