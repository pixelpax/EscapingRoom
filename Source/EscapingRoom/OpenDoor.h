// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPINGROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
    
    UPROPERTY(BlueprintAssignable)
    FOnOpenRequest OnOpenRequest;
    
    UPROPERTY(BlueprintAssignable)
    FOnCloseRequest OnCloseRequest;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere)
	float OpenAngle = 90.f;

    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate=nullptr;

    UPROPERTY(EditAnywhere)
	float DoorCloseDelay = .6f;
    

	AActor* ActorThatOpens=nullptr; // Remember that pawns inherit from actors!
    AActor* Owner=nullptr;

	float DoorOpenTime;
    bool DoorClosed = true;

	void OpenDoor();
    void CloseDoor();
    
    float GetTotalMassOnPlate();
};
