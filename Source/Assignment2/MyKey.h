// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MyKey.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT2_API AMyKey : public AStaticMeshActor
{
	GENERATED_BODY()
		
public:

	AMyKey();

	// Networking Stuff
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure)
		bool IsActive();
	
	UFUNCTION(BlueprintCallable)
		void setActive(bool NewState);

	FString GetObservation() { return observation; }
	
	virtual void GetPickedUp();

protected:

	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
		bool bIsActive;

	UPROPERTY(Replicated)
		FString observation;

	UFUNCTION()
		virtual void OnRep_IsActive();
	
};
