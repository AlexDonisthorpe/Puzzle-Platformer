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

	AMovingPlatform();
	
	protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	private:
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 1.f;
	
};
