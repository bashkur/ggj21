// Fill out your copyright notice in the Description page of Project Settings.


#include "DowsingTool.h"
#include "DrawDebugHelpers.h"

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
	FVector Loc;
	FRotator Rot;
	FHitResult Hit;

	APlayerController* player = UGameplayStatics::GetPlayerController(GetWorld(),0);
	player->GetPlayerViewPoint(Loc,Rot);
	TSet<UActorComponent*> components = player->GetOwner()->GetComponents();
	UAudioComponent* sound = nullptr;
	for (UActorComponent* c : components)
	{
		if (c->ComponentHasTag("Stick_Audio"))
		{
			sound = Cast<UAudioComponent>(c);
		}
	}
	FVector Start = Loc;
	FVector End = Start + (Rot.Vector()*2000);
	FCollisionQueryParams TraceParams;
	GetWorld()->LineTraceSingleByChannel(Hit,Start,End,ECC_Visibility,TraceParams);

	DrawDebugLine(GetWorld(),Start,End,FColor::Blue,false,5.0f);
	if (Hit.bBlockingHit)
	{
		V_LOG("Hit Something");
		if (Hit.GetComponent()->ComponentHasTag("Treasure_Ring"))
		{
			V_LOG("Found Treasure Ring!");
			if (sound)
			{
				sound->Play();
			}
		}
	}
}
