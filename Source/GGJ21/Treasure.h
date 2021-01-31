// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Treasure.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class GGJ21_API UTreasure : public UObject
{
	GENERATED_BODY()

	UTreasure();

	/**The mesh to display for this items pickup*/
	class UStaticMesh* PickupMesh;
};
