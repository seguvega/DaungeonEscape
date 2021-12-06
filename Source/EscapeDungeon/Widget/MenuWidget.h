// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeDungeon/Widget/FatherWidget.h"
#include "MenuWidget.generated.h"

class UFatherWidget;
class UButton;
class UWidgetSwitcher;

UCLASS()
class ESCAPEDUNGEON_API UMenuWidget : public UFatherWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MainWidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* MenuGeneral;

	UPROPERTY(meta = (BindWidget))
	UWidget* MenuInstrucciones;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Jugar;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_ComoJugar;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Atras;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Salir;


protected:
	virtual bool Initialize() override;

	UFUNCTION()
	void OnClickJugar();

	UFUNCTION()
	void OnClickComoJugar();

	UFUNCTION()
	void OnClickAtras();

	UFUNCTION()
	void OnClickSalir();
	
};
