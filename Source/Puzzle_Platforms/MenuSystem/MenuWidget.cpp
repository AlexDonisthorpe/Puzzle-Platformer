// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"


void UMenuWidget::SetMenuInterface(IMenuInterface* MMenuInterface)
{
	MenuInterface = MMenuInterface;
}

bool UMenuWidget::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if(!bSuccess) return bSuccess;

	this->bIsFocusable = true;
	this->AddToViewport();

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) return false;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController != nullptr)) return false;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(this->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(true);
	
	return true;
}

void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) return;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController != nullptr)) return;

	const FInputModeGameOnly InputMode;

	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(false);
}
