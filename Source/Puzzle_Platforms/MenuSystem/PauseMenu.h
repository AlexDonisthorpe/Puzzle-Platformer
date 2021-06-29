// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "PauseMenu.generated.h"

UCLASS()
class PUZZLE_PLATFORMS_API UPauseMenu : public UMenuWidget
{
	GENERATED_BODY()

	protected:
	virtual bool Initialize() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MenuButton;
	
	public:
	UFUNCTION()
	void Cancel();

	UFUNCTION()
	void MainMenu();
};
