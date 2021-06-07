#include "WeatherSystemConfig.h"

void UWeatherSystemConfig::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	PostPropertyChangedDelegate.Broadcast();
}
