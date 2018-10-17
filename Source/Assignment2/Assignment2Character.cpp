// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Assignment2Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Engine/World.h"
#include "Engine.h"
#include "MyKey.h"
#include "MyDoor.h"
#include "MyFuseBox.h"
#include "Net/UnrealNetwork.h"

//////////////////////////////////////////////////////////////////////////
// AAssignment2Character

AAssignment2Character::AAssignment2Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 0.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 160.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// *******************************************
	// ** My Code
	// *******************************************

	//Setup Variables
	health = 1.0f;
	damageAmount = 0.01f;
	damageRate = 1.0f;
	isDead = false;
	hasKey = false;
	interact = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAssignment2Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAssignment2Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAssignment2Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AAssignment2Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AAssignment2Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AAssignment2Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AAssignment2Character::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AAssignment2Character::OnResetVR);

	// ***************************
	// MY Code
	//****************************
	// Interact key binding
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AAssignment2Character::Interact);
}


void AAssignment2Character::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AAssignment2Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AAssignment2Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AAssignment2Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AAssignment2Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAssignment2Character::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AAssignment2Character::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

	// *******************************************
	// ** My Code
	// *******************************************

/*
void AAssignment2Character::BeginPlay()
{
}
*/

void AAssignment2Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAssignment2Character, hasKey);
	DOREPLIFETIME(AAssignment2Character, health);
	DOREPLIFETIME(AAssignment2Character, announcement);
}

void AAssignment2Character::Interact()
{
	//if (GEngine)
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Click!"));
	interact = true;
	CallMyTrace(interact);
	interact = false;
}



FString AAssignment2Character::MyRole()
{
	if (Role == ROLE_Authority)
	{
		return TEXT("Server");
	}
	else
	{
		return TEXT("Client");
	}
}

void AAssignment2Character::Tick(float DeltaTime)
{
	CallMyTrace(false);
	TakeGasDamage(DeltaTime);
	Super::Tick(DeltaTime);
}


void AAssignment2Character::TakeGasDamage(float DeltaTime)
{
	health -= damageAmount *DeltaTime;
}

bool AAssignment2Character::CheckIfDead()
{
	if (health <= 0) {
		return true;
	}
	else {
		return false;
	}
}

void AAssignment2Character::ClearPickupInfo() {
	observation = "";
}

FString AAssignment2Character::GetObservation() {
	return observation;
}

FString AAssignment2Character::GetAnnouncement() {
	return announcement;
}


//***************************************************************************************************
//** Trace functions - used to detect items we are looking at in the world
//***************************************************************************************************
//***************************************************************************************************

//***************************************************************************************************
//** Trace() - called by our CallMyTrace() function which sets up our parameters and passes them through
//***************************************************************************************************

bool AAssignment2Character::Trace(
	UWorld* World,
	TArray<AActor*>& ActorsToIgnore,
	const FVector& Start,
	const FVector& End,
	FHitResult& HitOut,
	ECollisionChannel CollisionChannel = ECC_Pawn,
	bool ReturnPhysMat = false
) {

	// The World parameter refers to our game world (map/level) 
	// If there is no World, abort
	if (!World)
	{
		return false;
	}

	// Set up our TraceParams object
	FCollisionQueryParams TraceParams(FName(TEXT("My Trace")), true, ActorsToIgnore[0]);

	// Should we simple or complex collision?
	TraceParams.bTraceComplex = true;

	// We don't need Physics materials 
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

	// Add our ActorsToIgnore
	TraceParams.AddIgnoredActors(ActorsToIgnore);

	// When we're debugging it is really useful to see where our trace is in the world
	// We can use World->DebugDrawTraceTag to tell Unreal to draw debug lines for our trace
	// (remove these lines to remove the debug - or better create a debug switch!)
	const FName TraceTag("MyTraceTag");
	World->DebugDrawTraceTag = TraceTag;
	TraceParams.TraceTag = TraceTag;


	// Force clear the HitData which contains our results
	HitOut = FHitResult(ForceInit);

	// Perform our trace
	World->LineTraceSingleByChannel
	(
		HitOut,		//result
		Start,	//start
		End, //end
		CollisionChannel, //collision channel
		TraceParams
	);

	// If we hit an actor, return true
	return (HitOut.GetActor() != NULL);
}

//***************************************************************************************************
//** CallMyTrace() - sets up our parameters and then calls our Trace() function
//***************************************************************************************************

void AAssignment2Character::CallMyTrace(bool interact)
{
	// Get the location of the camera (where we are looking from) and the direction we are looking in
	const FVector Start = FollowCamera->GetComponentLocation();
	const FVector ForwardVector = FollowCamera->GetForwardVector();

	// How for in front of our character do we want our trace to extend?
	// ForwardVector is a unit vector, so we multiply by the desired distance
	const FVector End = Start + ForwardVector * 256;

	// Force clear the HitData which contains our results
	FHitResult HitData(ForceInit);

	// What Actors do we want our trace to Ignore?
	TArray<AActor*> ActorsToIgnore;

	//Ignore the player character - so you don't hit yourself!
	ActorsToIgnore.Add(this);

	// Call our Trace() function with the paramaters we have set up
	// If it Hits anything
	if (Trace(GetWorld(), ActorsToIgnore, Start, End, HitData, ECC_Visibility, false))
	{
		// Process our HitData
		if (HitData.GetActor())
		{

			//UE_LOG(LogClass, Warning, TEXT("This a testing statement. %s"), *HitData.GetActor()->GetName());
			ProcessTraceHit(HitData, interact);

		}
		else
		{
			// The trace did not return an Actor
			// An error has occurred
			// Record a message in the error log
		}
	}
	else
	{
		// We did not hit an Actor
		ClearPickupInfo();

	}

}

//***************************************************************************************************
//** ProcessTraceHit() - process our Trace Hit result
//***************************************************************************************************

void AAssignment2Character::ProcessTraceHit(FHitResult& HitOut, bool interact)
{
	// Cast the actor to APickup
	AMyKey* const Key = Cast<AMyKey>(HitOut.GetActor());
	if (Key)
	{
		observation = Key->GetObservation();
		if (interact)
		{
			PickupKey(Key);
			//Key->GetPickedUp();
			//GameMode->GetPickedUp(Key);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Picked up key!"));
		}
		
	}

	AMyFuseBox* const FuseBox = Cast<AMyFuseBox>(HitOut.GetActor());
	if (FuseBox)
	{
		observation = FuseBox->GetObservation();
		if (interact) {
			PlaceFuse(FuseBox);
		}
	}


	AMyDoor* const Door = Cast<AMyDoor>(HitOut.GetActor());
	if (Door && Door->isDisabled())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Door!"));
		observation = Door->GetObservation();
		if (interact && hasKey)
		{
			Door->OpenDoor();
			hasKey = false;
			Door->Disable();
		}
		else if (interact && !hasKey) {
			observation = Door->GetNoKeyObservation();
		}

	}
		
}

// ******************************************************************************
// Key/Fuse Functions
void AAssignment2Character::PickupKey(AMyKey* key)
{
	if (Role == ROLE_Authority)
	{
		key->GetPickedUp();
		hasKey = true;
	}
	else
	{
		ServerPickupKey(key);
	}
}

void AAssignment2Character::ServerPickupKey_Implementation(AMyKey* key)
{
	PickupKey(key);
}

bool AAssignment2Character::ServerPickupKey_Validate(AMyKey* key)
{
	return true;
}
// ******************************************************************************

// ******************************************************************************
// FuseBox Functions
void AAssignment2Character::PlaceFuse(AMyFuseBox* fusebox)
{
	if (Role == ROLE_Authority)
	{
		fusebox->FusePlaced();
		hasKey = false;
	}
	else
	{
		ServerPlaceFuse(fusebox);
	}
}

void AAssignment2Character::ServerPlaceFuse_Implementation(AMyFuseBox* fusebox)
{
	PlaceFuse(fusebox);
}

bool AAssignment2Character::ServerPlaceFuse_Validate(AMyFuseBox* fusebox)
{
	return true;
}
// ******************************************************************************