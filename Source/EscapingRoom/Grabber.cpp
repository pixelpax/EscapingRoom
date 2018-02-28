// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerLocation;
	FRotator PlayerRotation;

    // Get player view point this tick
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			OUT PlayerLocation,
			OUT PlayerRotation
	);

//	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Position: %s"), *PlayerLocation.ToString(), *PlayerRotation.ToString());

	// Debug a vector out in front of the player
//	FVector LineTraceEnd = PlayerLocation + FVector(0.f, 100.f, 0.f);
	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * 100;


    //	DrawDebugLine(const UWorld *InWorld, const FVector &LineStart, const FVector &LineEnd, const FColor &Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f)
	DrawDebugLine(
			GetWorld(),
			PlayerLocation,
			LineTraceEnd,
            FColor(255, 0, 0),
			false,
			0.f,
			0.f,
			10.f
	);

	//

    // Ray-cast out to reach distance

    // See what we hit
}

