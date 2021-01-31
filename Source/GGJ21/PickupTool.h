// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseToolComponent.h"
#include "PickupTool.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GGJ21_API UPickupTool : public UBaseToolComponent
{
	GENERATED_BODY()
	
	public:	
	// Called to use the tool's primary function
	virtual void Use() override;

	//BP Pickup func
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Pickup();
};
