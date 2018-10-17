// Fill out your copyright notice in the Description page of Project Settings.

#include "MySwitch.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMySwitch::AMySwitch()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
	observation = "It's a switch";
	inactiveObservation = "It won't budge";
	fuseActivated = false;
}

void AMySwitch::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMySwitch, bIsActive);
	DOREPLIFETIME(AMySwitch, fuseActivated);
}

bool AMySwitch::IsActive()
{
	return bIsActive;
}

void AMySwitch::setActive(bool NewState)
{

	if (Role == ROLE_Authority)
	{
		bIsActive = NewState;
	}

}

void AMySwitch::OnRep_IsActive()
{
	//
}


bool AMySwitch::IsFuseActivated()
{

	if (fuseActivated)
	{
		return true;
	}
	return false;

}
// Called when the game starts or when spawned
void AMySwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMySwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

