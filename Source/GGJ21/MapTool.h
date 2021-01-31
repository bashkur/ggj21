// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseToolComponent.h"
#include "MapTool.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GGJ21_API UMapTool : public UBaseToolComponent
{
	GENERATED_BODY()

	protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called to use the tool's primary function
	virtual void Use() override;
};
