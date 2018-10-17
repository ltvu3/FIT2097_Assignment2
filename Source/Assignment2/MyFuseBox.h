// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFuseBox.generated.h"

UCLASS()
class ASSIGNMENT2_API AMyFuseBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyFuseBox();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure)
		bool IsActive();

	UFUNCTION(BlueprintCallable)
		void setActive(bool NewState);

	FString GetObservation() { return observation; }

	UFUNCTION(BlueprintImplementableEvent)
		void FusePlaced();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
		bool bIsActive;

	UPROPERTY(Replicated)
		FString observation;

	UFUNCTION()
		virtual void OnRep_IsActive();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
