// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"


UCLASS()
class PUZZLE_PLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
	
	private:
	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void BackToMain();
	
	UFUNCTION()
	void QuitGame();
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinMenuButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Join;

	UPROPERTY(meta = (BindWidget))
	class UButton* Back;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPAddressBox;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Quit;
	
	protected:
	virtual bool Initialize() override;

};


