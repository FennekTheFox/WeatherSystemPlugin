// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WeatherSystemEditorLibrary.generated.h"

class UMaterial;
class UTextureRenderTarget2D;
/**
 * 
 */
UCLASS()
class WEATHERSYSTEMEDITORMODULE_API UWeatherSystemEditorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UWeatherSystemEditorLibrary();

public:
	static UMaterial* M_RenderTargetToSlateBrush;
	static UTextureRenderTarget2D* OverviewRenderTarget;
};
