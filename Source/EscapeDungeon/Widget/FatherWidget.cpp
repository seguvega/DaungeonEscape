// Fill out your copyright notice in the Description page of Project Settings.


#include "FatherWidget.h"

bool UFatherWidget::Initialize()
{
	bool Success = Super::Initialize();
	return Success;
}

void UFatherWidget::SetupWidget()
{
	this->AddToViewport();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;
	FInputModeUIOnly UIInputMode;
	UIInputMode.SetWidgetToFocus(this->TakeWidget());
	UIInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(UIInputMode);
	PlayerController->SetShowMouseCursor(true);
}

void UFatherWidget::SetupSpecialWidget()
{
	this->AddToViewport();
	APlayerController* TempPlayerController = GetWorld()->GetFirstPlayerController();
	if (!TempPlayerController) return;
	FInputModeGameAndUI UIAndKeyboardInput;
	UIAndKeyboardInput.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	UIAndKeyboardInput.SetWidgetToFocus(this->TakeWidget());
	TempPlayerController->SetInputMode(UIAndKeyboardInput);
	TempPlayerController->SetShowMouseCursor(true);
}

void UFatherWidget::ChangeInputMode()
{
	this->RemoveFromViewport();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;
	FInputModeGameOnly GameInputMode;
	PlayerController->SetInputMode(GameInputMode);
	PlayerController->SetShowMouseCursor(false);
}

void UFatherWidget::SetInterface(IMenuInterface* MInterface)
{
	if (!MInterface) return;
	MenuInterface = MInterface;
}