// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFuseBox.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AMyFuseBox::AMyFuseBox()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
	observation = "It's a fuse box";
}

void AMyFuseBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyFuseBox, bIsActive);
	DOREPLIFETIME(AMyFuseBox, fuseIsPlaced);
}

bool AMyFuseBox::IsActive()
{
	return bIsActive;
}

void AMyFuseBox::setActive(bool NewState)
{

	if (Role == ROLE_Authority)
	{
		bIsActive = NewState;
	}

}

void AMyFuseBox::OnRep_IsActive()
{
	//
}

// Called when the game starts or when spawned
void AMyFuseBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyFuseBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

