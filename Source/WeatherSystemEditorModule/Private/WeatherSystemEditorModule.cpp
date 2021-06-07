// Copyright Epic Games, Inc. All Rights Reserved.

#include "WeatherSystemEditorModule.h"
#include "WSCEditor.h"
#include "AssetTypeActions_WSC.h"

#define LOCTEXT_NAMESPACE "FWeatherSystemPluginModule"

class UWeatherSystemConfig;

const FName WSCEditorAppIdentifier = FName(TEXT("CustomAssetEditorApp"));


void FWeatherSystemEditorModule::StartupModule()
{
	MenuExtensibilityManager = MakeShareable(new FExtensibilityManager);
	ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	RegisterWSCAssetActions(AssetTools, MakeShareable(new FAssetTypeActions_WSC()));

	WeatherCategory = AssetTools.RegisterAdvancedAssetCategory(TEXT("Weather System"), LOCTEXT("WeatherSystemCategory", "Weather System"));
}

void FWeatherSystemEditorModule::ShutdownModule()
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
		}
	}

	CreatedAssetTypeActions.Empty();
}

TSharedRef<IWSCEditor> FWeatherSystemEditorModule::CreateWSCEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UWeatherSystemConfig* WSC)
{
// Initialize and spawn a new custom asset editor with the provided parameters
	TSharedRef<FWSCEditor> NewCustomAssetEditor(new FWSCEditor());
	NewCustomAssetEditor->InitWSCEditor(Mode, InitToolkitHost, WSC);
	return NewCustomAssetEditor;
}


void FWeatherSystemEditorModule::RegisterWSCAssetActions(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWeatherSystemEditorModule, WeatherSystemEditorModule)