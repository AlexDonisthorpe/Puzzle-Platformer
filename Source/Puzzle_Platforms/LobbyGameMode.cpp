// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	++LobbyPlayerCount;

	if(LobbyPlayerCount >= 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("3 players in the lobby..."));
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	LobbyPlayerCount = FMath::Clamp(--LobbyPlayerCount, 0, 10);
}
