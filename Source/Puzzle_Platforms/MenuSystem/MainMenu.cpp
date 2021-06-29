// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

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

	return true;
}






