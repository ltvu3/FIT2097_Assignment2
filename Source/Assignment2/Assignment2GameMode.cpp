// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Assignment2GameMode.h"
#include "Assignment2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameNetworkManager.h"
#include "Engine/World.h"
#include "Engine.h"
#include "MyHUD.h"

AAssignment2GameMode::AAssignment2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// use our custom HUD class
	//HUDClass = AMyHUD::StaticClass();
}

void AAssignment2GameMode::BeginPlay()
{
	//PrintGameWorldInfo();
}

void AAssignment2GameMode::PrintGameWorldInfo()
{
	
	// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Engine/UWorld/index.html
	// Our UWorld is the top level object/container for all Actors and Components that exist in our Level/Map
	// It gives us access to the entire world from c++
	// *********************************************************************************************************
	UWorld* World = GetWorld();
	check(World);
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, TEXT("World Exists"));
	if (Role == ROLE_Authority)
	{
		/*
		//Iterate through all the actors in the world
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, TEXT("--------------------------------------"));
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, TEXT("A list of all the actors in the world:"));
		for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, ActorItr->GetName());
		}
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, TEXT("--------------------------------------"));

		// Print out some information from the GameNetworkManager
		// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/AGameNetworkManager/index.html
		// *********************************************************************************************************
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, TEXT("Some Networking info:"));
		AGameNetworkManager* MyNetworkManager = World->NetworkManager;
		int32 NetSpeed = MyNetworkManager->CalculatedNetSpeed();
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("NetSpeed, %d"), NetSpeed));
		int32 TotalNetBandwidth = MyNetworkManager->TotalNetBandwidth;
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("TotalNetBandwidth, %d"), TotalNetBandwidth));

		// Get all the characters in our world and print out their names
		// *********************************************************************************************************

		// Another method to get the player controller is to use UGameplayStatics
		//if (APlayerController* thisPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		//{
		//	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, TEXT("XXXXGot the first player controller"));
		//}
		*/
		// Use the World to get a list of all controllers
		// GetControllerIterator() gets both PlayerControllers and AIControllers
		for (FConstControllerIterator ContIT = World->GetControllerIterator(); ContIT; ++ContIT)
		{
			// So we need to check that we have a PlayerController
			if (APlayerController* myPlayerController = Cast<APlayerController>(*ContIT))
			{
				// And get the Pawn/Character the PlayerController is possessing
				if (AAssignment2Character* myCharacter = Cast<AAssignment2Character>(myPlayerController->GetPawn()))
				{
					// Once we have a pointer to the Character, we can call functions, set values etc. for that Character
					GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("Character's Name: %s"), *myCharacter->GetName()));
				}

			}
		}

	}
}
