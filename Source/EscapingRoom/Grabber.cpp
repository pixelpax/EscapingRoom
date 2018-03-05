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

	//UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for booty"));
	
    FindPhysicsComponent();
    FindInputComponent();
}

void UGrabber::FindPhysicsComponent()
{
    /// Look for attached physics handle
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle) {
        UE_LOG(LogTemp, Warning, TEXT("Successfully retrieved PhysicsHandle"));
    } else {
        UE_LOG(LogTemp, Error, TEXT("Attempted to get PhysicsHandle by type on Default Pawn Grabber, but none exists."));
    }

}

void UGrabber::FindInputComponent()
{
    /// Look for attached physics handle
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent) {
        UE_LOG(LogTemp, Warning, TEXT("Successfully grabbed input component"));
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::GrabReleased);
    } else {
        UE_LOG(LogTemp, Error, TEXT("Attempted to get InputComponent by type on Default Pawn Grabber, but none exists."));
    }
    
}

void UGrabber::Grab()
{
    /// Try and reach any actors with  phyics body collision channel set
    auto  HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto ActorHit = HitResult.GetActor();
    
    if (ActorHit) {
        /// if we hit something then attach a physics handle
        PhysicsHandle->GrabComponentAtLocation(
                                               ComponentToGrab,
                                               NAME_None,
                                               ComponentToGrab->GetOwner()->GetActorLocation()
                                               );
    }
}

void UGrabber::GrabReleased()
{
    PhysicsHandle->ReleaseComponent();
}



// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    // If the physics handle is attached
    // move the object that we're holding

	FVector PlayerLocation;
	FRotator PlayerRotation;

    // Get player view point this tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			OUT PlayerLocation,
			OUT PlayerRotation
	);

//	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Position: %s"), *PlayerLocation.ToString(), *PlayerRotation.ToString());

	// Debug a vector out in front of the player
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

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    

	/// Ray-cast out to reach distance
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(OUT Hit,
                                            PlayerLocation,
                                            LineTraceEnd,
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            TraceParameters);
    
	// See what we hit
	AActor* ActorHit = Hit.GetActor();
    if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Object hit: %s"), *(ActorHit->GetName()));
	}
    
    if (PhysicsHandle->GrabbedComponent)
    {
        PhysicsHandle->SetTargetLocation(LineTraceEnd);
    }
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
    
    // If the physics handle is attached
    // move the object that we're holding

	FVector PlayerLocation;
	FRotator PlayerRotation;

    // Get player view point this tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			OUT PlayerLocation,
			OUT PlayerRotation
	);

//	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Position: %s"), *PlayerLocation.ToString(), *PlayerRotation.ToString());

	// Debug a vector out in front of the player
	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * 100;
	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    

	/// Ray-cast out to reach distance
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(OUT Hit,
                                            PlayerLocation,
                                            LineTraceEnd,
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            TraceParameters);
    
	// See what we hit
	//AActor* ActorHit = Hit.GetActor();
    //if (ActorHit) {
	//	UE_LOG(LogTemp, Warning, TEXT("Object hit: %s"), *(ActorHit->GetName()));
	//}
    return Hit;
}
