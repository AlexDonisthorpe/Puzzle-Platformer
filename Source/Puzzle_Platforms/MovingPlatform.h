// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLE_PLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	
	AMovingPlatform();

	void AddActiveTrigger();
	void RemoveActiveTrigger();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category="Movement")
	float MoveSpeed = 1.f;
	UPROPERTY(EditAnywhere, Category="Movement", meta = (MakeEditWidget = true))
	FVector TargetLocation;

	FVector StartLocation;
	FVector TargetDirection;

	UPROPERTY(EditAnywhere, Category="Puzzle Configuration")
	int ActiveTriggers = 1;

};
