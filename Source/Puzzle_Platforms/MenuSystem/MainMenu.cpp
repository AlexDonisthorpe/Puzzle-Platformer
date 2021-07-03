// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "ServerRow.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"

UMainMenu::UMainMenu()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if(!ensure(ServerRowBPClass.Class != nullptr)) return;

	ServerRowClass = ServerRowBPClass.Class;
}

void UMainMenu::HostButtonClicked()
{
	if(!ensure(MenuInterface != nullptr)) return;
	MenuInterface->Host();
}

void UMainMenu::SetServerList(const TArray<FString> ServerNames)
{
	UWorld* World = this->GetWorld();
	if(!ensure(World != nullptr)) return;
	
	ServerList->ClearChildren();
	
	for(const FString& Server : ServerNames)
	{
		UServerRow* ServerRow = CreateWidget<UServerRow>(World, ServerRowClass);
		if(!ensure(ServerRow != nullptr)) return;
		
		ServerRow->ServerName->SetText(FText::FromString(Server));
		ServerList->AddChild(ServerRow);
	}
}

void UMainMenu::JoinServer()
{
	if(!ensure(MenuInterface != nullptr)) return;
	if(!ensure(ServerList != nullptr)) return;

	MenuInterface->Join("");
	
	//SetServerList();
}

void UMainMenu::OpenJoinMenu()
{
	if(!ensure(JoinMenu != nullptr)) return;
	if(!ensure(MenuSwitcher != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);

	if(!ensure(MenuInterface != nullptr)) return;
	MenuInterface->RefreshServerList();
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
	Join->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if(!ensure(Back != nullptr)) return false;
	Back->OnClicked.AddDynamic(this, &UMainMenu::BackToMain);
	
	if(!ensure(Quit != nullptr)) return false;
    Quit->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}






