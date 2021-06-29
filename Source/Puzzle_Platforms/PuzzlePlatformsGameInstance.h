// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

class UUserWidget;
class UMenuWidget;
UCLASS()
class PUZZLE_PLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

	UPuzzlePlatformsGameInstance();

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadPause();
	
	UFUNCTION(Exec)
	virtual void Host() override;

	UFUNCTION(Exec)
	virtual void Join(const FString& IPAddress) override;

	virtual void LoadMainMenu() override;
	
	private:
	TSubclassOf<UUserWidget> MainMenuClass;
	TSubclassOf<UUserWidget> PauseMenuClass;
};
