// Fill out your copyright notice in the Description page of Project Settings.


#include "TreasureInventoryComponent.h"

#include "Serialization/JsonTypes.h"

// Sets default values for this component's properties
UTreasureInventoryComponent::UTreasureInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTreasureInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UTreasureInventoryComponent::AddItem(UTreasure* Item)
{
	if(Item)
	{
		Items.Add(Item);
	}

	return true;
}

bool UTreasureInventoryComponent::RemoveItem(UTreasure* Item)
{
	if(Item)
	{
		Items.RemoveSingle(Item);
		return true;
	}
	return false;
}

