#pragma once

UCLASS(Blueprintable. BlueprintType)
class UWeatherSystemConfig : public UObject
{
	GENERATED_BODY()

public:
	UPROPERRTY(BlueprintReadOnly, EditAnywhere)
		FVector WorldOrigin;

	UPROPERRTY(BlueprintReadOnly, EditAnywhere)
		FVector WorldBounds;

};