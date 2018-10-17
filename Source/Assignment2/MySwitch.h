// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySwitch.generated.h"

UCLASS()
class ASSIGNMENT2_API AMySwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySwitch();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure)
		bool IsActive();

	UFUNCTION(BlueprintCallable)
		void setActive(bool NewState);

	FString GetObservation() { return observation; }
	FString GetInactiveObservation() { return inactiveObservation; }

	UFUNCTION(BlueprintImplementableEvent)
		void SwitchPulled();

	UFUNCTION(BlueprintCallable)
		bool IsFuseActivated();

	UFUNCTION(BlueprintCallable)
		void ActivateFuse() { fuseActivated = true; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
		bool bIsActive;

	UPROPERTY(Replicated)
		FString observation;

	UPROPERTY(Replicated)
		FString inactiveObservation;

	UPROPERTY(Replicated)
		bool fuseActivated;

	UFUNCTION()
		virtual void OnRep_IsActive();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
