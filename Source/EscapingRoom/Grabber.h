// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPINGROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
	// How far ahead of the player can we reach in centimeters
	UPROPERTY(EditAnywhere)
	float Reach = 100;
    
private:
    void FindPhysicsComponent();
    void FindInputComponent();
    
    void Grab();
    void GrabReleased();
    const FHitResult GetFirstPhysicsBodyInReach();
    
    UPhysicsHandleComponent* PhysicsHandle = nullptr;
    UInputComponent* InputComponent = nullptr;
    
};
