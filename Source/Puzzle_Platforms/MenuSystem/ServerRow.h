// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

class UMainMenu;
class UButton;
UCLASS()
class PUZZLE_PLATFORMS_API UServerRow : public UUserWidget
{
	GENERATED_BODY()
private:
	uint32 Index = 999;

	UPROPERTY()
	UMainMenu* Parent;
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;

	UPROPERTY(BlueprintReadOnly)
	bool Selected;

	void Setup(class UMainMenu* ParentMenu, uint32 IndexToSet);

	UPROPERTY(meta = (BindWidget))
	UButton* ServerButton;

	UFUNCTION()
	void OnClicked();
	
};
