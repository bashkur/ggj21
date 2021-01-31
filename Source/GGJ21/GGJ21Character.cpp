// Copyright Epic Games, Inc. All Rights Reserved.

#include "GGJ21Character.h"
#include "GGJ21Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "Blueprint/UserWidget.h"
#include "ShovelTool.h"
#include "DetectorTool.h"
#include "MapTool.h"
#include "DowsingTool.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AGGJ21Character

AGGJ21Character::AGGJ21Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	// Mesh1P->SetupAttachment(GetCapsuleComponent());
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// // Create a gun mesh component
	// FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	// FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	// FP_Gun->bCastDynamicShadow = false;
	// FP_Gun->CastShadow = false;
	// // FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	// FP_Gun->SetupAttachment(RootComponent);
	//
	// FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	// FP_MuzzleLocation->SetupAttachment(FP_Gun);
	// FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	ActiveTool = 0;
}

void AGGJ21Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	// FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	Mesh1P->SetHiddenInGame(false, true);

	if (HUDWidgetType)
	{
		MasterHUD = CreateWidget(GetWorld()->GetFirstPlayerController(), HUDWidgetType);
		if (MasterHUD)
		{
			MasterHUD->AddToViewport();
			ActiveTool = 0.f;
			V_LOG("Created Master HUD");
		}
	}

	Tools.Empty();
	for(int i=0; i<ToolTypes.Num(); i++)
	{
		Tools.Add(Cast<UBaseToolComponent>(FindComponentByClass(ToolTypes[i])));
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGGJ21Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//Bind for toggling map
	PlayerInputComponent->BindAction("ViewMap", IE_Pressed,this,&AGGJ21Character::ToggleMap);
	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AGGJ21Character::UseTool);


	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AGGJ21Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGGJ21Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGGJ21Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGGJ21Character::LookUpAtRate);

	// Bind hotbar item selection keys
	PlayerInputComponent->BindAction("NextTool", IE_Pressed, this, &AGGJ21Character::NextTool);
	PlayerInputComponent->BindAction("PreviousTool", IE_Pressed, this, &AGGJ21Character::PreviousTool);
}

void AGGJ21Character::NextTool()
{
	// if(ActiveTool >= Tools.Num()-1)
	if(ActiveTool >= 3)						// TODO: temp fix. Change to list based number.
	{
		ActiveTool = 0;
	}
	else
	{
		ActiveTool++;
	}
	// V_LOGNAME("New tool is ", Tools[ActiveTool%4]);
	int cur = FMath::Abs(ActiveTool % 4);
	V_LOGI("Nxt tool! active tool = ", cur);
	UpdateActiveTool(cur);
}

void AGGJ21Character::PreviousTool()
{
	if(ActiveTool <= 0)
	{
		// ActiveTool = Tools.Num() - 1;
		ActiveTool = 3;				// TODO: temp fix. Change to list based number.
	}
	else
	{
		ActiveTool--;
	}
	// V_LOGNAME("New tool is ", Tools[ActiveTool%4]);
	int cur = FMath::Abs(ActiveTool % 4);
	V_LOGI("Prev tool! active tool = ", cur)
	UpdateActiveTool(cur);
}

void AGGJ21Character::UseTool()
{
	UBaseToolComponent* Tool = Cast<UBaseToolComponent>(Tools[ActiveTool]);
	if(IsValid(Tool))
	{
		Tool->Use();
	}
}

void AGGJ21Character::OnFire()
{
	// try and fire a projectile
	// if (ProjectileClass != NULL)
	// {
	// 	UWorld* const World = GetWorld();
	// 	if (World != NULL)
	// 	{
	// 		const FRotator SpawnRotation = GetControlRotation();
	// 		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	// 		const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
	//
	// 		//Set Spawn Collision Handling Override
	// 		FActorSpawnParameters ActorSpawnParams;
	// 		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	//
	// 		// spawn the projectile at the muzzle
	// 		World->SpawnActor<AGGJ21Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	// 	}
	// }
	//
	// // try and play the sound if specified
	// if (FireSound != NULL)
	// {
	// 	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	// }
	//
	// // try and play a firing animation if specified
	// if (FireAnimation != NULL)
	// {
	// 	// Get the animation object for the arms mesh
	// 	UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
	// 	if (AnimInstance != NULL)
	// 	{
	// 		AnimInstance->Montage_Play(FireAnimation, 1.f);
	// 	}
	// }
}


void AGGJ21Character::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AGGJ21Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AGGJ21Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGGJ21Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
