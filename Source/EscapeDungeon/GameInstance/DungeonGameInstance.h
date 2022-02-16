// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EscapeDungeon/Interfaces/MenuInterface.h"
#include "DungeonGameInstance.generated.h"

class UUserWidget;
class UMenuWidget;
class UPlayerHud;
class UInGameMenuWidget;
class IMenuInterface;

UCLASS()
class ESCAPEDUNGEON_API UDungeonGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CreateMainMenu();

	void CreateInGameMenu();

	void CreatePlayerHud();

	void RestartInputMode();

	void SendKeys(FString Keys);

	void SendIsGrabbing(bool IsGrab);

	void SendPlayerFps(FString StringFps);

	void EndGame();

protected:
	UDungeonGameInstance(const FObjectInitializer& ObjectInitializer);
	///PURE Functions
	virtual void Play();

	virtual void Exit();

	virtual void Reiniciar();

	virtual void SalirJuego();

	virtual void ExecCommand(FString Command);
	///End PURE Functions

private:
	TSubclassOf<UUserWidget> UserWidgetClass;

	TSubclassOf<UUserWidget> InGameMenuWidgetClass;

	TSubclassOf<UUserWidget> PlayerHudClass;

	UMenuWidget* MenuWidget;

	UInGameMenuWidget* InGameMenuWidget;

	UPlayerHud* PlayerHud;
};