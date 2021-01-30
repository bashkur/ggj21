// Fill out your copyright notice in the Description page of Project Settings.


#include "MapTool.h"

void UMapTool::BeginPlay()
{
	Super::BeginPlay();
}

void UMapTool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMapTool::Use()
{
	V_LOG("Using Map Tool!");
}
