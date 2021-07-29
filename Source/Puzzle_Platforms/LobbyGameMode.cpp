// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "PuzzlePlatformsGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	++LobbyPlayerCount;

	if(LobbyPlayerCount >= 2)
	{
		
		GetWorldTimerManager().SetTimer(GameStartTimer, this, &ALobbyGameMode::ServerTravel, 10.f, false);
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	LobbyPlayerCount = FMath::Clamp(--LobbyPlayerCount, 0, 10);
}

void ALobbyGameMode::ServerTravel()
{
	auto GameInstance = Cast<UPuzzlePlatformsGameInstance>(GetGameInstance());

	if(GameInstance == nullptr) return;

	GameInstance->StartSession();
	
	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) return;

	bUseSeamlessTravel = true;
	World->ServerTravel("/Game/PuzzleComponents/Maps/ThirdPersonExampleMap?listen");
}
