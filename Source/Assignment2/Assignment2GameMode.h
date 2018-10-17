// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Assignment2GameMode.generated.h"

UCLASS(minimalapi)
class AAssignment2GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAssignment2GameMode();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	void PrintGameWorldInfo();

	FString announcement;

	UFUNCTION(BlueprintPure)
		FString GetAnnouncement() { return announcement; }
	
	UFUNCTION(BlueprintCallable)
		void SetAnnouncement(FString announce) { announcement = announce; }

};



