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

void UMainMenu::SetServerList(const TArray<FServerData> ServerDetails)
{
	UWorld* World = this->GetWorld();
	if(!ensure(World != nullptr)) return;
	
	ServerList->ClearChildren();

	uint32 RowIndex = 0;
	
	for(const FServerData& Server : ServerDetails)
	{
		UServerRow* ServerRow = CreateWidget<UServerRow>(World, ServerRowClass);
		if(!ensure(ServerRow != nullptr)) return;
		
		ServerRow->ServerName->SetText(FText::FromString(Server.HostUsername));
		ServerRow->Setup(this, RowIndex);

		++RowIndex;
		
		ServerList->AddChild(ServerRow);
	}
}

void UMainMenu::SelectIndex(const uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}

void UMainMenu::UpdateChildren()
{
	TArray<UWidget*> Children = ServerList->GetAllChildren();
	
	for (int i = 0; i < Children.Num(); ++i)
	{
		UServerRow* Child = static_cast<UServerRow*>(Children[i]);

		if(Child != nullptr)
		{
			Child->Selected = SelectedIndex.IsSet() && SelectedIndex.GetValue() == i;
		}
	}	
}

void UMainMenu::JoinServer()
{
	if(!ensure(MenuInterface != nullptr)) return;
	if(SelectedIndex.IsSet())
	{
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index not set"));
	}
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






