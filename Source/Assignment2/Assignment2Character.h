// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Assignment2Character.generated.h"

UCLASS(config=Game)
class AAssignment2Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AAssignment2Character();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

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

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// My Code - Interact function
	void Interact();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	// *******************************************
	// ** My Code
	// *******************************************

	UFUNCTION(BlueprintPure)
		FString MyRole();

	virtual void Tick(float DeltaTime) override;

	//virtual void BeginPlay() override;

	void TakeDamage();

	bool CheckIfDead();

	void ClearPickupInfo();

	UFUNCTION(BlueprintPure)
		FString GetObservation();

	// Character Variables
	FString observation;
	float health;
	float damageAmount;
	float damageRate;
	float startingDamageRate;
	float sprintValue;
	float walkValue;
	float sprintDamageModifier;
	bool isDead;
	bool hasKey;
	bool hasFuse;
	bool hasTorch;
	bool disableSprint;

	bool lookingAtKey;

	UFUNCTION(BlueprintPure)
		float getHealth() { return health; }
	
	UFUNCTION(BlueprintPure)
		bool getHasKey() { return hasKey; }
	
	UFUNCTION(BlueprintPure)
		bool getHasFuse() { return hasFuse; }



	//***************************************************************************************************
	//** Trace functions - used to detect items we are looking at in the world
	//** Adapted from code found on the unreal wiki https://wiki.unrealengine.com/Trace_Functions
	//***************************************************************************************************

	bool Trace(
		UWorld* World,
		TArray<AActor*>& ActorsToIgnore,
		const FVector& Start,
		const FVector& End,
		FHitResult& HitOut,
		ECollisionChannel CollisionChannel,
		bool ReturnPhysMat
	);

	void CallMyTrace();

	void ProcessTraceHit(FHitResult& HitOut);

};