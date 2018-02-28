// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{

	FRotator NewRotation = FRotator(0.f, OpenAngle, 00.f);
	Owner->SetActorRotation(NewRotation);
	DoorOpenTime = GetWorld()->GetTimeSeconds();
}

void UOpenDoor::CloseDoor()
{
	FRotator NewRotation = FRotator(0.f, 0.f, 00.f);
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume each frame
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {

		// If the player is in the volume, open the door
		OpenDoor();
	}

	// Check if it's time to close the door
	float curTime = GetWorld()->GetTimeSeconds();
	if (curTime - DoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}
}

