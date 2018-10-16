// Fill out your copyright notice in the Description page of Project Settings.

#include "MyKey.h"
#include "Net/UnrealNetwork.h"

AMyKey::AMyKey()
{
	bReplicates = true;
	bAlwaysRelevant = true;
	PrimaryActorTick.bCanEverTick = false;

	observation = "Left Click to pick up the key";

	// The pickup is moveable and has physics enabled
	//bReplicateMovement = true;
	//GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	//GetStaticMeshComponent()->SetSimulatePhysics(true);
}

void AMyKey::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyKey, bIsActive);
}

bool AMyKey::IsActive()
{
	return bIsActive;
}

void AMyKey::setActive(bool NewState)
{
	if (Role == ROLE_Authority)
	{
		bIsActive = NewState;
	}
}

void AMyKey::GetPickedUp()
{
	Destroy();
}

void AMyKey::OnRep_IsActive()
{
	// Some code goes here
}


