#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class UWeatherSystemConfig;

/**
 * Public interface to Custom Asset Editor
 */
class IWSCEditor : public FAssetEditorToolkit
{
public:
	/** Retrieves the current custom asset. */
	virtual UWeatherSystemConfig* GetWSC() = 0;

	/** Set the current custom asset. */
	virtual void SetWSC( UWeatherSystemConfig* InCustomAsset) = 0;
};