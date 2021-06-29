// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::AddActiveTrigger()
{
	++ActiveTriggers;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	--ActiveTriggers;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	StartLocation = GetActorLocation();

	// Target location is local by default, so we need to convert it to global
	TargetLocation = GetTransform().TransformPosition(TargetLocation);

	// Get the normalised direction of the target location from the start
	TargetDirection = (TargetLocation - StartLocation).GetSafeNormal();
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(ActiveTriggers > 0)
	{
		FVector CurrentLocation = GetActorLocation();
		
		float JourneyLength = (TargetLocation - StartLocation).Size();
		float JourneyTravelled = (CurrentLocation - StartLocation).Size();
	
		// This is nice, but if the platform moves faster than the check, it'll never turn around...
		if(JourneyTravelled >= JourneyLength)
		{
			Swap(StartLocation, TargetLocation);
			TargetDirection *= -1;
		}
	
		SetActorLocation(CurrentLocation + TargetDirection * DeltaSeconds * MoveSpeed);		
	}

}
