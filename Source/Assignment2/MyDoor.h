// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyDoor.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT2_API AMyDoor : public AActor
{
	GENERATED_BODY()
	
public:
	AMyDoor();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool IsActive();

	void setActive(bool NewState);

	FString observation;
	FString noKeyObservation;

	FString GetObservation() { return observation; }
	FString GetNoKeyObservation() { return observation; }

	UFUNCTION(BlueprintImplementableEvent)
		void OpenDoor();

	bool disabled;
	void Disable() { disabled = true; }
	bool isDisabled() { return disabled; }

protected:

	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
		bool bIsActive;

	UFUNCTION()
		virtual void OnRep_IsActive();
	
	
};
