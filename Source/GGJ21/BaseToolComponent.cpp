#include "BaseToolComponent.h"

UBaseToolComponent::UBaseToolComponent()
{
}

void UBaseToolComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBaseToolComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBaseToolComponent::Use()
{
	V_LOG("You used me!");
}
