// Copyright Epic Games, Inc. All Rights Reserved.

#include "WeatherSystemEditorModule.h"
#include "WSCEditor.h"

#define LOCTEXT_NAMESPACE "FWeatherSystemPluginModule"

class UWeatherSystemConfig;

const FName WSCEditorAppIdentifier = FName(TEXT("CustomAssetEditorApp"));


void FWeatherSystemEditorModule::StartupModule()
{
	MenuExtensibilityManager.Reset();
	ToolBarExtensibilityManager.Reset();

	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		// Unregister our custom created assets from the AssetTools
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 i = 0; i < CreatedAssetTypeActions.Num(); ++i)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[i].ToSharedRef());
			WeatherCategory = AssetTools.RegisterAdvancedAssetCategory(TEXT("Weather System"), LOCTEXT("WeatherSystemCategory", "Weather System"));
		}
	}

	CreatedAssetTypeActions.Empty();
}

void FWeatherSystemEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

TSharedRef<IWSCEditor> FWeatherSystemEditorModule::CreateWSCEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UWeatherSystemConfig* WSC)
{
// Initialize and spawn a new custom asset editor with the provided parameters
	TSharedRef<FWSCEditor> NewCustomAssetEditor(new FWSCEditor());
	NewCustomAssetEditor->InitWSCEditor(Mode, InitToolkitHost, WSC);
	return NewCustomAssetEditor;
}


void FWeatherSystemEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWeatherSystemEditorModule, WeatherSystemEditorModule)