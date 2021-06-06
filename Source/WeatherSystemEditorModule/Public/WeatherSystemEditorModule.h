// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IWSCEditor.h"
#include "ICustomAssetEditorModule.h"

class UWeatherSystemConfig;


static EAssetTypeCategories::Type WeatherCategory;

class FWeatherSystemEditorModule : public ICustomAssetEditorModule
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual TSharedRef<IWSCEditor> CreateWSCEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UWeatherSystemConfig* CustomAsset) override;
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);
	/** Gets the extensibility managers for outside entities to extend custom asset editor's menus and toolbars */
	virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override { return MenuExtensibilityManager; }
	virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override { return ToolBarExtensibilityManager; }



	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;

private:
	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;
	TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;
};
