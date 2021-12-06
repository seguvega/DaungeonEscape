// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenuWidget.h"
#include "Components/Button.h"

bool UInGameMenuWidget::Initialize()
{
	bool ValidWidget = Super::Initialize();
	(!Button_Reiniciar ? ValidWidget = false : ValidWidget);
	Button_Reiniciar->OnClicked.AddDynamic(this, &UInGameMenuWidget::OnClickReiniciar);
	(!Button_FinJuego ? ValidWidget = false : ValidWidget);
	Button_FinJuego->OnClicked.AddDynamic(this, &UInGameMenuWidget::OnClickFinJuego);
	(!Button_Salir ? ValidWidget = false : ValidWidget);
	Button_Salir->OnClicked.AddDynamic(this, &UInGameMenuWidget::OnClickSalir);
	
	return ValidWidget;
}


void UInGameMenuWidget::OnClickReiniciar()
{
	if (!MenuInterface) return;
	MenuInterface->Reiniciar();
}

void UInGameMenuWidget::OnClickFinJuego()
{
	if (!MenuInterface) return;
	MenuInterface->SalirJuego();
}

void UInGameMenuWidget::OnClickSalir()
{
	if (!MenuInterface) return;
	MenuInterface->Exit();
}