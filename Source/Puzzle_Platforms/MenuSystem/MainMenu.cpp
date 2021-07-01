// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenu::HostButtonClicked()
{
	if(!ensure(MenuInterface != nullptr)) return;
	MenuInterface->Host();
}

void UMainMenu::JoinButtonClicked()
{
	if(!ensure(MenuInterface != nullptr)) return;
	if(!ensure(IPAddressBox != nullptr)) return;

	const FString& IPString = IPAddressBox->Text.ToString();
	if(IPString.IsEmpty()) return;
	
	MenuInterface->Join(IPString);
}

void UMainMenu::OpenJoinMenu()
{
	if(!ensure(JoinMenu != nullptr)) return;
	if(!ensure(MenuSwitcher != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::BackToMain()
{
	if(!ensure(MenuSwitcher != nullptr)) return;
	MenuSwitcher->SetActiveWidget(this);
}

void UMainMenu::QuitGame()
{
	if(!ensure(Quit != nullptr)) return;

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(World != nullptr)) return;
	
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
}

bool UMainMenu::Initialize()
{
	Super::Initialize();
	
	if(!ensure(Host != nullptr)) return false;
	Host->OnClicked.AddDynamic(this, &UMainMenu::HostButtonClicked);

	if(!ensure(JoinMenuButton != nullptr)) return false;
	JoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	
	if(!ensure(Join != nullptr)) return false;
	Join->OnClicked.AddDynamic(this, &UMainMenu::JoinButtonClicked);

	if(!ensure(Back != nullptr)) return false;
	Back->OnClicked.AddDynamic(this, &UMainMenu::BackToMain);
	
	if(!ensure(Quit != nullptr)) return false;
    Quit->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}






