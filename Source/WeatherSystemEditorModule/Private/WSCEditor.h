#pragma once

#include "CoreMinimal.h"
#include "Toolkits/IToolkitHost.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Editor/PropertyEditor/Public/PropertyEditorDelegates.h"
#include "IWSCEditor.h"

class IDetailsView;
class SDockableTab;
class UWeatherSystemConfig;
class USceneCaptureComponent2D;
class UMaterialInstanceDynamic;

/**
 *
 */
class WEATHERSYSTEMEDITORMODULE_API FWSCEditor : public IWSCEditor
{

public:
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;

	/**
	 * Edits the specified asset object
	 *
	 * @param	Mode					Asset editing mode for this editor (standalone or world-centric)
	 * @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within
	 * @param	InCustomAsset			The Custom Asset to Edit
	 */
	void InitWSCEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UWeatherSystemConfig* InCustomAsset);

	/** Destructor */
	virtual ~FWSCEditor();

	/** Begin IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual bool IsPrimaryEditor() const override { return true; }
	/** End IToolkit interface */

/** Begin ICustomAssetEditor initerface */
	virtual UWeatherSystemConfig* GetWSC() override;
	virtual void SetWSC(UWeatherSystemConfig* InCustomAsset) override;
	/** End ICustomAssetEditor initerface */

private:
	uint32 CalculateOrthoWidth();
	void SynchronizeProperties();

private:
	/** Create the properties tab and its content */
	TSharedRef<SDockTab> SpawnPropertiesTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnOverviewTab(const FSpawnTabArgs& Args);

	/** Dockable tab for properties */
	TSharedPtr< SDockableTab > PropertiesTab;

	/** Details view */
	TSharedPtr<class IDetailsView> DetailsView;

	/**	The tab ids for all the tabs used */
	static const FName PropertiesTabId;
	static const FName OverviewTabId;
	static const FName ToolkitFName;

	UWeatherSystemConfig* WSC;

	//Overview Tab Stuff
	FSlateBrush OverviewBrush;
	AActor* OverviewCameraActor;
	USceneCaptureComponent2D* OveriviewCaptureComponent;
	UMaterialInstanceDynamic* OverviewMID;
	uint32 OrthoWidth;
};

