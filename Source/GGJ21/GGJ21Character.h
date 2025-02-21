// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "BaseToolComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GGJ21Character.generated.h"

class UInputComponent;

UCLASS(config=Game)
class AGGJ21Character : public ACharacter
{
	GENERATED_BODY()
	
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	// /** Gun mesh: 1st person view (seen only by self) */
	// UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	// class USkeletalMeshComponent* FP_Gun;
	//
	// /** Location on gun mesh where projectiles should spawn. */
	// UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	// class USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	AGGJ21Character();

protected:
	virtual void BeginPlay();

public:
	//Active Tool Number -> 0 = map, 1 = pickup, 2 = detector, 3 = shovel
	UPROPERTY(BlueprintReadOnly)
	int ActiveTool;
	
	//List of Available Tool Types to be set in BP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tools)
	TArray<TSubclassOf<class UActorComponent>> ToolTypes;

	//List of Available Tools
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tools)
	TArray<UBaseToolComponent*> Tools;
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AGGJ21Projectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditDefaultsOnly, Category=UI)
	TSubclassOf<class UUserWidget> HUDWidgetType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=UI)
	UUserWidget* MasterHUD;

protected:

	//Get next tool
	void NextTool();

	//Get next tool
	void PreviousTool();

	//Use the active tool
	void UseTool();
	
	/** Fires a projectile. */
	void OnFire();

	// Call this function when the active tool changes. Implemented in Character BP.
	UFUNCTION(BlueprintImplementableEvent, Category = "Custom Events")
	void UpdateActiveTool(int CurrentToolIdx);

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

