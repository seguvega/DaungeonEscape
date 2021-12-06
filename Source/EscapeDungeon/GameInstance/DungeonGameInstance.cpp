// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "EscapeDungeon/Widget/MenuWidget.h"
#include "EscapeDungeon/Widget/InGameMenuWidget.h"


UDungeonGameInstance::UDungeonGameInstance(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WBPMainMenu(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!WBPMainMenu.Class) return;
	UserWidgetClass = WBPMainMenu.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> WBPInGameMenu(TEXT("/Game/MenuSystem/WPB_InGameMenu"));
	if (!WBPInGameMenu.Class) return;
	InGameMenuWidgetClass = WBPInGameMenu.Class;
}

void UDungeonGameInstance::CreateMainMenu()
{
	MenuWidget = CreateWidget<UMenuWidget>(this, UserWidgetClass);
	if (!MenuWidget) return;
	MenuWidget->SetupWidget();
	MenuWidget->SetInterface(this);
}

void UDungeonGameInstance::CreateInGameMenu()
{
	InGameMenuWidget = CreateWidget<UInGameMenuWidget>(this, InGameMenuWidgetClass);
	if (!InGameMenuWidget) return;
	InGameMenuWidget->SetupSpecialWidget();
	InGameMenuWidget->SetInterface(this);
}

void UDungeonGameInstance::Play()
{
	UWorld* World = GetWorld();
	if (!World) return;
	if (!MenuWidget) return;
	MenuWidget->ChangeInputMode();
	World->ServerTravel("/Game/Maps/Dungeon?listen");
}

void UDungeonGameInstance::Reiniciar()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!PlayerController) return;
	if (!InGameMenuWidget) return;
	InGameMenuWidget->ChangeInputMode();
	PlayerController->RestartLevel(); // revisar
}

void UDungeonGameInstance::SalirJuego()
{
	UWorld* ThisWorld = GetWorld();
	if (!ThisWorld) return;
	ThisWorld->ServerTravel("/Game/Maps/Menu");
}

void UDungeonGameInstance::RestartInputMode()
{
	if (!InGameMenuWidget) return;
	InGameMenuWidget->ChangeInputMode();
}

void UDungeonGameInstance::Exit()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!PlayerController) return;
	PlayerController->ConsoleCommand(FString("Exit"));
}

