// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherSystemEditorLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Engine/TextureRenderTarget2D.h"

UMaterial* UWeatherSystemEditorLibrary::M_RenderTargetToSlateBrush = nullptr;
UTextureRenderTarget2D* UWeatherSystemEditorLibrary::OverviewRenderTarget = nullptr;

UWeatherSystemEditorLibrary::UWeatherSystemEditorLibrary()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> M_RenderTargetToSlateBrush_Finder (TEXT("Material'/WeatherSystemPlugin/Materials/M_RenderTargetToSlateBrush.M_RenderTargetToSlateBrush'"));
	if (M_RenderTargetToSlateBrush_Finder.Succeeded())
		M_RenderTargetToSlateBrush = M_RenderTargetToSlateBrush_Finder.Object;

	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> OverviewRenderTarget_Finder(TEXT("TextureRenderTarget2D'/WeatherSystemPlugin/Textures/OverviewRenderTarget.OverviewRenderTarget'"));
	if (OverviewRenderTarget_Finder.Succeeded())
		OverviewRenderTarget = OverviewRenderTarget_Finder.Object;
}
