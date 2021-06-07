#include "WSCFactoryNew.h"
#include "WeatherSystemConfig.h"



UWSCFactoryNew::UWSCFactoryNew()
{
	SupportedClass = UWeatherSystemConfig::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;

}

UObject* UWSCFactoryNew::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UWeatherSystemConfig>(InParent, InClass, InName, Flags);
}

bool UWSCFactoryNew::ShouldShowInNewMenu() const
{
	return true;
}