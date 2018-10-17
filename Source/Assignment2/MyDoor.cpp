// Fill out your copyright notice in the Description page of Project Settings.

#include "MyDoor.h"
#include "Net/UnrealNetwork.h"


AMyDoor::AMyDoor()
{

	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
	bIsActive = true;
	bReplicateMovement = true;
}
/*
void AMyDoor::OpenDoor() {
	FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f);
	FQuat QuatRotation = FQuat(NewRotation);
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}*/

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


