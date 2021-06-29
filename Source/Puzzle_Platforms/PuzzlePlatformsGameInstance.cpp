// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance()
{
	static ConstructorHelpers::FClassFinder<UMainMenu> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if(!ensure(MenuBPClass.Class != nullptr)) return;

	MainMenuClass = MenuBPClass.Class;
	
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Init: Found Class: %s"), *MainMenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MainMenuClass != nullptr)) return;
	
	UMainMenu* MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
	if(!ensure(MainMenu != nullptr)) return;

	MainMenu->SetMenuInterface(this);
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

	const FString Message = FString::Printf(TEXT("Joining ... %s"), *IPAddress);

	Engine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, Message, true, FVector2D(1));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if(!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(IPAddress, TRAVEL_Absolute);
}
