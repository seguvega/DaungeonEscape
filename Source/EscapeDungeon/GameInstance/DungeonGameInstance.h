// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EscapeDungeon/Interfaces/MenuInterface.h"
#include "DungeonGameInstance.generated.h"

class UUserWidget;
class UMenuWidget;
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

	void RestartInputMode();

protected:
	UDungeonGameInstance(const FObjectInitializer& ObjectInitializer);

	void Play() override;

	void Exit() override;

	void Reiniciar() override;

	void SalirJuego() override;

private:
	TSubclassOf<UUserWidget> UserWidgetClass;

	TSubclassOf<UUserWidget> InGameMenuWidgetClass;

	UMenuWidget* MenuWidget;

	UInGameMenuWidget* InGameMenuWidget;
};
