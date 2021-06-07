#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "WeatherSystemConfig.generated.h"

DECLARE_MULTICAST_DELEGATE(FPropertyChangedDelegate)

UCLASS(Blueprintable, BlueprintType)
class WEATHERSYSTEMMODULE_API UWeatherSystemConfig : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector WorldOrigin;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FIntPoint WorldBounds;


	FPropertyChangedDelegate PostPropertyChangedDelegate;

	
#if WITH_EDITOR
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};