// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectorTool.h"

void UDetectorTool::BeginPlay()
{
	Super::BeginPlay();
}

void UDetectorTool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDetectorTool::Use()
{
	V_LOG("Using Detector Tool!");
}
