#pragma once

// #include "CoreMinimal.h"
#include "Engine/Canvas.h"
#include "Engine/TextureRenderTarget2D.h"
#include "UObject/UnrealTypePrivate.h"
#include "UnrealTerminalContext.generated.h"

USTRUCT()
struct FUnrealTerminalContext 
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UCanvas> CanvasObject;

	UPROPERTY()
	UCanvas* Canvas;

	UPROPERTY()
	UTextureRenderTarget2D* RenderTarget;
	
	UPROPERTY()
	FUintVector2 Size;
	
};
