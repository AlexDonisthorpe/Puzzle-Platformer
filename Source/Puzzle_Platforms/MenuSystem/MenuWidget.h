// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MenuInterface.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLE_PLATFORMS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
	void SetMenuInterface(IMenuInterface* MMenuInterface);
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	protected:
	virtual bool Initialize() override;
	IMenuInterface* MenuInterface;
};
