// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance()
{
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
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
