// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

USTRUCT()
struct FServerData
{
	GENERATED_BODY()
	
	FString Name;
	uint8 CurrentPlayers;
	uint8 MaxPlayers;
	FString HostUsername;
};

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

	 void UpdateChildren();
	
	protected:
	virtual bool Initialize() override;

	public:
	void SetServerList(TArray<FServerData> ServerDetails);
	void SelectIndex(uint32 Index);

};


