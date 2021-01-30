// Fill out your copyright notice in the Description page of Project Settings.


#include "DowsingTool.h"

void UDowsingTool::BeginPlay()
{
	Super::BeginPlay();
}

void UDowsingTool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDowsingTool::Use()
{
	V_LOG("Using Dowsing Tool!");
}
