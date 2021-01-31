// Fill out your copyright notice in the Description page of Project Settings.


#include "ShovelTool.h"

void UShovelTool::BeginPlay()
{
	Super::BeginPlay();
}

void UShovelTool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UShovelTool::Use()
{
	V_LOG("Using Shovel Tool!");
	Dig();
}

void UShovelTool::Dig_Implementation()
{
	V_LOG("Inside Implementation.");
}
