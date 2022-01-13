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

protected:
	UDungeonGameInstance(const FObjectInitializer& ObjectInitializer);

	void Play() override;

	void Exit() override;

	void Reiniciar() override;

	void SalirJuego() override;

	void ExecCommand(FString Command) override;

private:
	TSubclassOf<UUserWidget> UserWidgetClass;

	TSubclassOf<UUserWidget> InGameMenuWidgetClass;

	TSubclassOf<UUserWidget> PlayerHudClass;

	UMenuWidget* MenuWidget;

	UInGameMenuWidget* InGameMenuWidget;

	UPlayerHud* PlayerHud;
};
