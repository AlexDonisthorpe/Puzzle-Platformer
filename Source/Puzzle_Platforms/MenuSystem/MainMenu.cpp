// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"

void UMainMenu::HostButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Host Button Clicked"));
}

void UMainMenu::JoinButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Join Button Clicked"));
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


