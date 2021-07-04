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

	UMainMenu();
	
	private:
	UFUNCTION()
	void HostButtonClicked();
	

	UFUNCTION()
	void JoinServer();

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
	class UPanelWidget* ServerList;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Quit;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ServerRowClass;
	
	TOptional<uint32> SelectedIndex;
	
	protected:
	virtual bool Initialize() override;

	public:
	void SetServerList(TArray<FString> ServerNames);
	void SelectIndex(uint32 Index);

};


