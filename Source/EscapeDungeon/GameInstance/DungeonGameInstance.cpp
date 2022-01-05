// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "EscapeDungeon/Widget/MenuWidget.h"
#include "EscapeDungeon/Widget/InGameMenuWidget.h"
#include "EscapeDungeon/Widget/PlayerHud.h"


UDungeonGameInstance::UDungeonGameInstance(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WBPMainMenu(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!WBPMainMenu.Class) return;
	UserWidgetClass = WBPMainMenu.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> WBPInGameMenu(TEXT("/Game/MenuSystem/WPB_InGameMenu"));
	if (!WBPInGameMenu.Class) return;
	InGameMenuWidgetClass = WBPInGameMenu.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> WBPPlayerHUD(TEXT("/Game/MenuSystem/WBP_PlayerHud"));
	if (!WBPPlayerHUD.Class) return;
	PlayerHudClass = WBPPlayerHUD.Class;
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

void UDungeonGameInstance::CreatePlayerHud()
{
	PlayerHud = CreateWidget<UPlayerHud>(this, PlayerHudClass);
	if(!PlayerHud) return;
	PlayerHud->AddToViewport();
	PlayerHud->SetInterface(this);
}

void UDungeonGameInstance::Play()
{
	UWorld* World = GetWorld();
	if (!World) return;
	if (!MenuWidget) return;
	MenuWidget->ChangeInputMode();
	World->ServerTravel("/Game/Maps/Dungeon");
}

void UDungeonGameInstance::Reiniciar()
{
	UWorld* World = GetWorld();
	if (!World) return;
	if (!InGameMenuWidget) return;
	InGameMenuWidget->ChangeInputMode();
	World->ServerTravel("/Game/Maps/Dungeon", false);
	//PlayerController->RestartLevel(); // revisar 	ClientTravel( TEXT("?restart"), TRAVEL_Relative );
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

void UDungeonGameInstance::SendKeys(FString Keys)
{
	if (!PlayerHud) return;
	//UE_LOG(LogTemp, Warning, TEXT("GameInstance Num %s"), *Keys);
	PlayerHud->SetText(Keys);
}

void UDungeonGameInstance::Exit()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!PlayerController) return;
	PlayerController->ConsoleCommand(FString("Exit"));
}
