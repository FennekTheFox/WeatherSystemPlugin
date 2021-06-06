#pragma once

#include "Factories/Factory.h"
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "WSCFactoryNew.generated.h"


UCLASS()
class UWSCFactoryNew : public UFactory
{
	GENERATED_BODY()

	UWSCFactoryNew();

public:
	

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool ShouldShowInNewMenu() const override;
};