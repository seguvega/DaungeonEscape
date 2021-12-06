// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeDungeon/Widget/FatherWidget.h"
#include "InGameMenuWidget.generated.h"

class UFatherWidget;
class UButton;

UCLASS()
class ESCAPEDUNGEON_API UInGameMenuWidget : public UFatherWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Reiniciar;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_FinJuego;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Salir;

protected:
	virtual bool Initialize() override;


private:
	UFUNCTION()
	void OnClickReiniciar();

	UFUNCTION()
	void OnClickFinJuego();

	UFUNCTION()
	void OnClickSalir();
};
