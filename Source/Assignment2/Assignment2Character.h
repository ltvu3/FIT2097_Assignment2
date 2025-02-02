// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyKey.h"
#include "MyFuseBox.h"
#include "MySwitch.h"
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
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// *******
	// Key/Fuse Functions 
	virtual void PickupKey(AMyKey* key);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerPickupKey(AMyKey* key);
		void ServerPickupKey_Implementation(AMyKey* key);
		bool ServerPickupKey_Validate(AMyKey* key);
	// ********

	// ********
	// FuseBox Functions
	virtual void PlaceFuse(AMyFuseBox* fusebox);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerPlaceFuse(AMyFuseBox* fusebox);
		void ServerPlaceFuse_Implementation(AMyFuseBox* fusebox);
		bool ServerPlaceFuse_Validate(AMyFuseBox* fusebox);
	// *******


	// ********
	// Switch Functions
	virtual void PullSwitch(AMySwitch* aswitch);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerPullSwitch(AMySwitch* aswitch);
		void ServerPullSwitch_Implementation(AMySwitch* aswitch);
		bool ServerPullSwitch_Validate(AMySwitch* aswitch);
	// *******
	UFUNCTION(BlueprintPure)
		FString MyRole();

	virtual void Tick(float DeltaTime) override;

	//virtual void BeginPlay() override;

	void TakeGasDamage(float DeltaTime);

	bool CheckIfDead();

	void ClearPickupInfo();

	UFUNCTION(BlueprintCallable)
		void SetObservation(FString newObservation) { observation = newObservation; }

	UFUNCTION(BlueprintPure)
		FString GetObservation();

	UPROPERTY(Replicated)
		FString announcement;

	UFUNCTION(BlueprintPure)
		FString GetAnnouncement();

	virtual void SetAnnouncement(FString announce);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSetAnnouncement(const FString& announce);
		void ServerSetAnnouncement_Implementation(const FString& announce) { announcement = announce; }
		bool ServerSetAnnouncement_Validate(const FString& announce) { return true; }

		/*
	UFUNCTION(Client, Reliable)
		void ClientSetAnnouncement(const FString& announce);
		void ClientSetAnnouncement_Implementation(const FString& announce) {announcement = announce; }
		bool ClientSetAnnouncement_Validate(const FString& announce) { return true; }
		*/

	UPROPERTY(Replicated)
		float health;

	UFUNCTION(BlueprintPure)
		float getHealth() { return health; }

	UPROPERTY(Replicated)
		bool hasKey;

	UFUNCTION(BlueprintPure)
		bool getHasKey() { return hasKey; }

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void setHasKey(bool aBool);
		void setHasKey_Implementation(bool aBool) { hasKey = aBool; }
		bool setHasKey_Validate(bool aBool) { return true; }

	FString observation;
	float damageAmount;
	float damageRate;
	bool isDead;
	bool interact;


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

	void CallMyTrace(bool interact);

	void ProcessTraceHit(FHitResult& HitOut, bool interact);

};