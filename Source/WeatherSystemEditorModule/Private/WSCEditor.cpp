#include "WSCEditor.h"
#include "Modules/ModuleManager.h"
#include "EditorStyleSet.h"
#include "Widgets/Docking/SDockTab.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "Editor.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "WeatherSystemEditorModule.h"
#include "ICustomAssetEditorModule.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#define LOCTEXT_NAMESPACE "WSCEditor"

const FName FWSCEditor::ToolkitFName(TEXT("WSCEditor"));
const FName FWSCEditor::PropertiesTabId(TEXT("WSCEditor_Properties"));
const FName FWSCEditor::OverviewTabId(TEXT("WSCEditor_Overview"));


void FWSCEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	// Add a new workspace menu category to the tab manager
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_CustomAssetEditor", "Custom Asset Editor"));

	// We register the tab manager to the asset editor toolkit so we can use it in this editor
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	// Register the properties tab spawner within our tab manager
	// We provide the function with the identiefier for this tab and a shared pointer to the
	// SpawnPropertiesTab function within this editor class
	// Additionaly, we provide a name to be displayed, a category and the tab icon
	InTabManager->RegisterTabSpawner(PropertiesTabId, FOnSpawnTab::CreateSP(this, &FWSCEditor::SpawnPropertiesTab))
		.SetDisplayName(LOCTEXT("PropertiesTab", "Details"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));
	InTabManager->RegisterTabSpawner(OverviewTabId, FOnSpawnTab::CreateSP(this, &FWSCEditor::SpawnOverviewTab))
		.SetDisplayName(LOCTEXT("PropertiesTab", "Details"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));
}

void FWSCEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	// Unregister the tab manager from the asset editor toolkit
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	// Unregister our custom tab from the tab manager, making sure it is cleaned up when the editor gets destroyed
	InTabManager->UnregisterTabSpawner(PropertiesTabId);
	InTabManager->UnregisterTabSpawner(OverviewTabId);
}

uint32 FWSCEditor::CalculateOrthoWidth()
{
	if(WSC)
		return FMath::Max(WSC->WorldBounds.X, WSC->WorldBounds.Y) + 500;

	return 1;
}

void FWSCEditor::SynchronizeProperties()
{
	OrthoWidth = CalculateOrthoWidth();
	if (OveriviewCaptureComponent)
		OveriviewCaptureComponent->OrthoWidth = OrthoWidth;
}

TSharedRef<SDockTab> FWSCEditor::SpawnPropertiesTab(const FSpawnTabArgs& Args)
{
	// Make sure we have the correct tab id
	check(Args.GetTabId() == PropertiesTabId);

	// Return a new slate dockable tab that contains our details view
	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("GenericEditor.Tabs.Properties"))
		.Label(LOCTEXT("GenericDetailsTitle", "Details"))
		.TabColorScale(GetTabColorScale())
		[
			// Provide the details view as this tab its content
			DetailsView.ToSharedRef()
		];
}


TSharedRef<SDockTab> FWSCEditor::SpawnOverviewTab(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == OverviewTabId);

	OrthoWidth = CalculateOrthoWidth();

	OverviewCameraActor = GWorld->SpawnActorDeferred<AActor>(AActor::StaticClass(), FTransform::Identity);

	OveriviewCaptureComponent = NewObject<USceneCaptureComponent2D>(OverviewCameraActor, TEXT("OveriviewSceneCapture"));
	OverviewCameraActor->SetRootComponent(OveriviewCaptureComponent);
	OveriviewCaptureComponent->RegisterComponent();

	OveriviewCaptureComponent->TextureTarget = UWeatherSystemEditorLibrary::OverviewRenderTarget;
	OveriviewCaptureComponent->ProjectionType = ECameraProjectionMode::Type::Orthographic;
	OveriviewCaptureComponent->OrthoWidth = CalculateOrthoWidth();

	OverviewCameraActor->SetActorLocation(WSC->WorldOrigin+FVector(0.0f,0.0f,100000.0f));
	OverviewCameraActor->SetActorRotation(FRotator(270.0f,0.0f,0.0f));

	OverviewMID = UMaterialInstanceDynamic::Create(UWeatherSystemEditorLibrary::M_RenderTargetToSlateBrush, WSC, TEXT("OverviewRenderToSlateBrush"));
	OverviewMID->SetTextureParameterValue(TEXT("RenderTarget"), UWeatherSystemEditorLibrary::OverviewRenderTarget);

	OverviewBrush = UWidgetBlueprintLibrary::MakeBrushFromMaterial(OverviewMID, OrthoWidth, OrthoWidth);

	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("GenericEditor.Tabs.Viewport"))
		.Label(LOCTEXT("GenericOverviewTitle", "Overview"))
		.TabColorScale(GetTabColorScale())
		[
			SNew(SImage)
			.Image(&OverviewBrush)
		];
}


void FWSCEditor::InitWSCEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UWeatherSystemConfig* InWSC)
{
	// Cache some values that will be used for our details view arguments
	const bool bIsUpdatable = false;
	const bool bAllowFavorites = true;
	const bool bIsLockable = false;

	// Set this InCustomAsset as our editing asset
	SetWSC(InWSC);

	// Retrieve the property editor module and assign properties to DetailsView
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs(bIsUpdatable, bIsLockable, true, FDetailsViewArgs::ObjectsUseNameArea, false);
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	// Create the layout of our custom asset editor
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_WeatherSystemConfigEditor_Layout_v1")
		->AddArea
		(
			// Create a vertical area and spawn the toolbar
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->SetHideTabWell(true)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetHideTabWell(true)
					->SetSizeCoefficient(2)
					->AddTab(OverviewTabId, ETabState::OpenedTab)					
				)
				->Split
				(

					// Split the tab and pass the tab id to the tab spawner
					FTabManager::NewSplitter()
					->Split
					(
						FTabManager::NewStack()
						->AddTab(PropertiesTabId, ETabState::OpenedTab)
					)
				)
			)
		);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;

	// Initialize our custom asset editor
	FAssetEditorToolkit::InitAssetEditor(
		Mode,
		InitToolkitHost,
		WSCEditorAppIdentifier,
		StandaloneDefaultLayout,
		bCreateDefaultStandaloneMenu,
		bCreateDefaultToolbar,
		(UObject*)InWSC);

	// Set the asset we are editing in the details view
	if (DetailsView.IsValid())
	{
		DetailsView->SetObject((UObject*)WSC);
	}
}

FWSCEditor::~FWSCEditor()
{    
	if(OverviewCameraActor)
		OverviewCameraActor->Destroy();

// On destruction we reset our tab and details view 
	DetailsView.Reset();
	PropertiesTab.Reset();
}

FName FWSCEditor::GetToolkitFName() const
{
	return ToolkitFName;
}

FText FWSCEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Custom Asset Editor");
}


FText FWSCEditor::GetToolkitToolTipText() const
{
	return LOCTEXT("ToolTip", "Custom Asset Editor");
}

FString FWSCEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "AnimationDatabase ").ToString();
}

FLinearColor FWSCEditor::GetWorldCentricTabColorScale() const
{
	return FColor::Red;
}

UWeatherSystemConfig* FWSCEditor::GetWSC()
{
	return WSC;
}

void FWSCEditor::SetWSC(UWeatherSystemConfig* InWSC)
{
	if (WSC)
	{
		WSC->PostPropertyChangedDelegate.RemoveAll(this);
	}

	WSC = InWSC;

	if (WSC)
	{
		WSC->PostPropertyChangedDelegate.AddRaw(this, &FWSCEditor::SynchronizeProperties);
	}
}




#undef LOCTEXT_NAMESPACE