// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"

#include "MainMenu.h"
#include "Components/Button.h"

void UServerRow::Setup(UMainMenu* ParentMenu, uint32 IndexToSet)
{
	Parent = ParentMenu;
	Index = IndexToSet;
	
	if(!ensure(ServerButton != nullptr)) return;
	ServerButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
}

void UServerRow::OnClicked()
{
	if(!ensure(Parent != nullptr)) return;
	Parent->SelectIndex(Index);
}



