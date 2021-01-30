// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Chaos/AABBTree.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GGJ21_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
	ACustomPlayerController();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Custom Settings")
	TSubclassOf<class UUserWidget> HUDWidgetType;

	UPROPERTY(BlueprintReadWrite)
	int CurrentTool;

	protected:
	UUserWidget* PlayerHUD;
};
