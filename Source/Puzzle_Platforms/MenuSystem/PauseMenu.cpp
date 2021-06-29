// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"

bool UPauseMenu::Initialize()
{
	bool Success = Super::Initialize();
	if(!Success) return false;

	if(!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UPauseMenu::Cancel);

	if(!ensure(MenuButton != nullptr)) return false;
	MenuButton->OnClicked.AddDynamic(this, &UPauseMenu::MainMenu);
	
	return true;	
}

void UPauseMenu::Cancel()
{
	RemoveFromViewport();
	
	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) return;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController != nullptr)) return;

	const FInputModeGameOnly InputMode;

	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(false);
}

void UPauseMenu::MainMenu()
{
	if(!ensure(MenuInterface != nullptr)) return;
	Cancel();
	MenuInterface->LoadMainMenu();
}
