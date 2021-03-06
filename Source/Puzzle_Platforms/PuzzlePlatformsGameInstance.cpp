// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "GameMapsSettings.h"
#include "OnlineSessionSettings.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuWidget.h"
#include "OnlineSubsystem.h"
#include "MenuSystem/MainMenu.h"

const static FName GSession_Name = TEXT("Session0");

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if(!ensure(MenuBPClass.Class != nullptr)) return;

	MainMenuClass = MenuBPClass.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> PauseBPClass(TEXT("/Game/MenuSystem/WBP_PauseMenu"));
	if(!ensure(PauseBPClass.Class != nullptr)) return;

	PauseMenuClass = PauseBPClass.Class;
}

UPuzzlePlatformsGameInstance::~UPuzzlePlatformsGameInstance()
{

}

void UPuzzlePlatformsGameInstance::Init()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if(!ensure(Subsystem != nullptr)) return;

	SessionInterface = Subsystem->GetSessionInterface();
	if(!SessionInterface.IsValid()) return;
	UE_LOG(LogTemp, Warning, TEXT("Found session interface"));

	SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
	SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnDestroySessionComplete);
	SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnFindSessionComplete);
	SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnJoinSessionComplete);

	if(GEngine != nullptr)
	{
		GEngine->OnNetworkFailure().AddUObject(this, &UPuzzlePlatformsGameInstance::OnNetworkFailure);
	}
}

void UPuzzlePlatformsGameInstance::LoadMenuWidget()
{
	if (!ensure(MainMenuClass != nullptr)) return;
	
	MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
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

void UPuzzlePlatformsGameInstance::CreatePuzzleSession() const
{
	// Technically following the flow we shouldn't need this check...
	if(SessionInterface)
	{
		FOnlineSessionSettings Settings;
		Settings.bIsLANMatch = true;
		Settings.NumPublicConnections = 2;
		Settings.bShouldAdvertise = true;
		Settings.bUsesPresence = true;
		
		SessionInterface->CreateSession(0, GSession_Name, Settings);		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create session, No Session Interface found."));
	}

}

void UPuzzlePlatformsGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		if(SessionInterface->GetNamedSession(GSession_Name))
		{
			SessionInterface->DestroySession(GSession_Name);
		}
		else
		{
			CreatePuzzleSession();
		}
	}
}

void UPuzzlePlatformsGameInstance::Join(const uint32 Index)
{
	if(!SessionInterface.IsValid()) return;
	if(!SessionSearch.IsValid()) return;
	SessionInterface->JoinSession(0, GSession_Name, SessionSearch->SearchResults[Index]);

}

void UPuzzlePlatformsGameInstance::StartSession()
{
	if(SessionInterface.IsValid())
	{
		SessionInterface->StartSession(GSession_Name);
	}
}

void UPuzzlePlatformsGameInstance::OnJoinSessionComplete(const FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if(!SessionInterface.IsValid()) return;
	
	FString ConnectInfo;
	if(SessionInterface->GetResolvedConnectString(SessionName, ConnectInfo))
	{
		UE_LOG(LogTemp, Warning, TEXT("Connect Info: %s"), *ConnectInfo);
	
		APlayerController* PlayerController = GetFirstLocalPlayerController();
		if(!ensure(PlayerController != nullptr)) return;
	
		PlayerController->ClientTravel(ConnectInfo, TRAVEL_Absolute);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not fetch connect string"));
	}

}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if(!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	if(SessionSearch.IsValid())
	{
		SessionSearch->MaxSearchResults = 10000;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		UE_LOG(LogTemp, Warning, TEXT("Looking for sessions..."));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UPuzzlePlatformsGameInstance::OnFindSessionComplete(const bool Success)
{
	if(Success && SessionSearch.IsValid())
	{
		if(SessionSearch->SearchResults.Num() >= 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found Session"));
			
			TArray<FServerData> ServerDetails;
			for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
			{
				FServerData Data;
				Data.Name = *SearchResult.GetSessionIdStr();
				Data.HostUsername = *SearchResult.Session.OwningUserName;
				Data.MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections;
				Data.CurrentPlayers = SearchResult.Session.NumOpenPublicConnections;
				
				 ServerDetails.Add(Data);
			}
			MainMenu->SetServerList(ServerDetails);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Sessions Found"));
		}

	}
}

void UPuzzlePlatformsGameInstance::OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	UE_LOG(LogTemp, Warning, TEXT("Network Failure"));
	LoadMainMenu();
}

void UPuzzlePlatformsGameInstance::OnCreateSessionComplete(const FName SessionName, const bool SessionStarted)
{
	if (SessionStarted)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Session Created"), *SessionName.ToString());

		UEngine* Engine = GetEngine();
		if(!ensure(Engine != nullptr)) return;
	
		UWorld* World = GetWorld();
		if(!ensure(World != nullptr)) return;

		World->ServerTravel("/Game/PuzzleComponents/Maps/Lobby?listen");
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Session could not be created"));
	}
}

void UPuzzlePlatformsGameInstance::OnDestroySessionComplete(const FName SessionName, const bool DestroySuccessful)
{
	if(DestroySuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Session destroyed, creating new session..."));
		CreatePuzzleSession();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't destroy session %s"), *SessionName.ToString());
	}
}

