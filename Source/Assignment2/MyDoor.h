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

	UFUNCTION(BlueprintImplementableEvent)
		void OpenDoor();

protected:

	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
		bool bIsActive;

	UFUNCTION()
		virtual void OnRep_IsActive();
	
	
};
