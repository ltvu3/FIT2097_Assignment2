// Fill out your copyright notice in the Description page of Project Settings.

#include "MyDoor.h"
#include "Net/UnrealNetwork.h"


AMyDoor::AMyDoor()
{

	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
	observation = "Left click to open door";
	noKeyObservation = "It requires a key";
	bIsActive = true;
	disabled = false;
	bReplicateMovement = true;
}

void AMyDoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyDoor, bIsActive);
}

bool AMyDoor::IsActive()
{
	return bIsActive;
}

void AMyDoor::setActive(bool NewState)
{

	if (Role == ROLE_Authority)
	{
		bIsActive = NewState;
	}

}

void AMyDoor::OnRep_IsActive()
{
	// Some code goes here
}


