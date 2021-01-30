// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "Blueprint/UserWidget.h"

ACustomPlayerController::ACustomPlayerController()
{
}

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetType)
	{
		PlayerHUD = CreateWidget(this, HUDWidgetType);
		if (PlayerHUD)
		{
			PlayerHUD->AddToViewport();

			CurrentTool = 0;
		}
	}
}
