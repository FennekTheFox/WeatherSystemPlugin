#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "ModuleManager.h"
#include "Toolkits/AssetEditorToolkit.h"

class ICustomAssetEditor;
class UWeatherSystemConfig;

extern const FName WSCEditorAppIdentifier;

/**
 * Custom Asset editor module interface
 */
class ICustomAssetEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility
{
public:
	/**
	 * Creates a new custom asset editor.
	 */
	virtual TSharedRef<ICustomAssetEditor> CreateCustomAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMyCustomAsset* CustomAsset) = 0;
};