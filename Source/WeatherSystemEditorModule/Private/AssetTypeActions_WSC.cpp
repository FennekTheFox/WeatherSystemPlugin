#include "AssetTypeActions_WSC.h"
#include "WeatherSystemEditorModule.h"
#include "WeatherSystemConfig.h"
#include "ICustomAssetEditorModule.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions_WSC"

FText FAssetTypeActions_WSC::GetName() const
{
	return NSLOCTEXT("AssetTypeActions_WSC", "AssetTypeActions_WSC", "WeatherSystemConfig");
}

FColor FAssetTypeActions_WSC::GetTypeColor() const
{
	return FColor::Magenta;
}

UClass* FAssetTypeActions_WSC::GetSupportedClass() const
{
	return UWeatherSystemConfig::StaticClass();
}

uint32 FAssetTypeActions_WSC::GetCategories()
{
	return WeatherCategory;
}

void FAssetTypeActions_WSC::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto MyCustomAsset = Cast<UWeatherSystemConfig>(*ObjIt);
		if (MyCustomAsset != NULL)
		{
			ICustomAssetEditorModule* WSCEditor = &FModuleManager::LoadModuleChecked<ICustomAssetEditorModule>("WeatherSystemEditorModule");
			WSCEditor->CreateWSCEditor(Mode, EditWithinLevelEditor, MyCustomAsset);
		}
	}
}

#undef LOCTEXT_NAMESPACE