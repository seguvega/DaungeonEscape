// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EscapeDungeon/Interfaces/MenuInterface.h"
#include "FatherWidget.generated.h"

class IMenuInterface;

UCLASS()
class ESCAPEDUNGEON_API UFatherWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupWidget();

	void SetupSpecialWidget();

	void ChangeInputMode();

	void SetInterface(IMenuInterface* MInterface);

protected:
	virtual bool Initialize() override;

	IMenuInterface* MenuInterface;
};
