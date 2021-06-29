// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

class UUserWidget;
class UMainMenu;
UCLASS()
class PUZZLE_PLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

	UPuzzlePlatformsGameInstance();
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();
	
	UFUNCTION(Exec)
	virtual void Host() override;

	UFUNCTION(Exec)
	virtual void Join(const FString& IPAddress) override;

	private:
	TSubclassOf<UMainMenu> MainMenuClass;
	
};
