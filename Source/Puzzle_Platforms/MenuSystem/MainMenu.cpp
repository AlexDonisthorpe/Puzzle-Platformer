// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"

void UMainMenu::SetMenuInterface(IMenuInterface* MMenuInterface)
{
	MenuInterface = MMenuInterface;
}

void UMainMenu::HostButtonClicked()
{
	if(!ensure(MenuInterface != nullptr)) return;
	MenuInterface->Host();
}

void UMainMenu::JoinButtonClicked()
{
	if(!ensure(MenuInterface != nullptr)) return;
	MenuInterface->Join("127.0.0.1");
}

bool UMainMenu::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if(!bSuccess) return bSuccess;

	if(!ensure(Host != nullptr)) return false;
	Host->OnClicked.AddDynamic(this, &UMainMenu::HostButtonClicked);

	if(!ensure(Join != nullptr)) return false;
	Join->OnClicked.AddDynamic(this, &UMainMenu::JoinButtonClicked);
	
	return true;
}


