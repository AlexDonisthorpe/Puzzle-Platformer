// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"


UCLASS()
class PUZZLE_PLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	public:
	void SetMenuInterface(IMenuInterface* MMenuInterface);
	
	private:
	IMenuInterface* MenuInterface;
	
	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* Join;

	protected:
	
	virtual bool Initialize() override;
};


