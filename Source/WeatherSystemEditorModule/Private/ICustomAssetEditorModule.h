#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
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

	virtual TSharedRef<IWSCEditor> CreateWSCEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UWeatherSystemConfig* CustomAsset) = 0;
};