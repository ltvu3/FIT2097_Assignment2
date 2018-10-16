// Fill out your copyright notice in the Description page of Project Settings.

#include "MyKey.h"
#include "Net/UnrealNetwork.h"
#include "Engine.h"

AMyKey::AMyKey()
{

	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
	observation = "Left Click to pick up the key";
	disabled = false;
	bAlwaysRelevant = true;
	bReplicateMovement = true;
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	GetStaticMeshComponent()->SetSimulatePhysics(true);

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


void AMyKey::ServerPickedUp_Implementation()
{
	SetActorHiddenInGame(true);
	Disable();
}

bool AMyKey::ClientPickedUp_Validate()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Validate TRUE"));
	return true;
}

void AMyKey::ClientPickedUp_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Picked up key!"));
	SetActorHiddenInGame(true);
	Disable();
}

void AMyKey::GetPickedUp() {
	if (Role == ROLE_Authority)
	{
		ServerPickedUp();
	}
	else
	{
		ClientPickedUp_Implementation();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ClientPickedUp()"));
	}
}

void AMyKey::OnRep_IsActive()
{
	GetPickedUp();
}


