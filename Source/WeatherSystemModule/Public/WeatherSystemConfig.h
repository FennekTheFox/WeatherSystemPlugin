#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "WeatherSystemConfig.generated.h"


UCLASS(Blueprintable, BlueprintType)
class WEATHERSYSTEMMODULE_API UWeatherSystemConfig : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector WorldOrigin;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector WorldBounds;

};