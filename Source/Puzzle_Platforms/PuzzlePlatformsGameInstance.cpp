// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuWidget.h"
#include "MenuSystem/PauseMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if(!ensure(MenuBPClass.Class != nullptr)) return;

	MainMenuClass = MenuBPClass.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> PauseBPClass(TEXT("/Game/MenuSystem/WBP_PauseMenu"));
	if(!ensure(PauseBPClass.Class != nullptr)) return;

	PauseMenuClass = PauseBPClass.Class;
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MainMenuClass != nullptr)) return;
	
	UMenuWidget* MainMenu = CreateWidget<UMenuWidget>(this, MainMenuClass);
	if(!ensure(MainMenu != nullptr)) return;

	MainMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadPause()
{
	if (!ensure(MainMenuClass != nullptr)) return;
	
	UMenuWidget* PauseMenu = CreateWidget<UMenuWidget>(this, PauseMenuClass);
	if(!ensure(PauseMenu != nullptr)) return;

	PauseMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if(!ensure(Engine != nullptr)) return;
	
	Engine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Host Message"), true, FVector2D(1));

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& IPAddress)
{
	if(IPAddress.IsEmpty()) return;
	
	UEngine* Engine = GetEngine();
	if(!ensure(Engine != nullptr)) return;

	// Debug Text
	const FString Message = FString::Printf(TEXT("Joining ... %s"), *IPAddress);
	Engine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, Message, true, FVector2D(1));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if(!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(IPAddress, TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if(!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", TRAVEL_Absolute);
}

