// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupTool.h"

void UPickupTool::Use()
{
	V_LOG("Used Pickup Tool!");
	Pickup();
}

void UPickupTool::Pickup_Implementation()
{
}
