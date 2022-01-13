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
	//MenuPrincipal
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MainWidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* MenuGeneral;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Jugar;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Opciones;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_ComoJugar;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Salir;
	//End MenuPrincipal

	//SubMenuInstrucciones
	UPROPERTY(meta = (BindWidget))
	UWidget* MenuInstrucciones;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Atras;
	//End SubMenuInstrucciones

	//SubMenuConfiguraciones
	UPROPERTY(meta = (BindWidget))
	UWidget* MenuSettings;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Atras_Opciones;
	//End SubMenuConfiguraciones

	//Botones Config
	//Resolucion
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonR720;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonR1280;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonR1920;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonR2560;

	//Distancia de Dibujado
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonVDCerca;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonVDMedio;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonVDLejos;

	//AntiAliasing
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonAALow;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonAAMed;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonAAHigh;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonAAUltra;

	//Sombras
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonSLow;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonSMed;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonSHigh;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonSUltra;

	//Texturas
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonTLow;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonTMed;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonTHigh;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonTUltra;
	//End Botones Config

protected:
	virtual bool Initialize() override;

	//MenuPrincipal
	UFUNCTION()
	void OnClickJugar();

	UFUNCTION()
	void OnClickOpciones();

	UFUNCTION()
	void OnClickComoJugar();

	UFUNCTION()
	void OnClickSalir();

	//SubMenuInstrucciones
	UFUNCTION()
	void OnClickAtras();

	//SubMenuInstrucciones
	UFUNCTION()
	void OnClickAtrasOpciones();

	///Botones Config
	//Resolución
	UFUNCTION()
	void OnclickButtonR720();

	UFUNCTION()
	void OnClickButtonR1280();

	UFUNCTION()
	void OnClickButtonR1920();

	UFUNCTION()
	void OnClickButtonR2560();
	//End Resolución

	//Distancia de Dibujado
	UFUNCTION()
	void OnClickButtonVDCerca();

	UFUNCTION()
	void OnClickButtonVDMedio();

	UFUNCTION()
	void OnClickButtonVDLejos();
	//End Distancia de Dibujado

	//AntiAliasing
	UFUNCTION()
	void OnClickButtonAALow();

	UFUNCTION()
	void OnClickButtonAAMed();

	UFUNCTION()
	void OnClickButtonAAHigh();

	UFUNCTION()
	void OnClickButtonAAUltra();
	//End AntiAliasing

	//Sombras
	UFUNCTION()
	void OnClickButtonSLow();

	UFUNCTION()
	void OnClickButtonSMed();

	UFUNCTION()
	void OnClickButtonSHigh();

	UFUNCTION()
	void OnClickButtonSUltra();
	//End Sombras

	//Texturas
	UFUNCTION()
	void OnClickButtonTLow();

	UFUNCTION()
	void OnClickButtonTMed();

	UFUNCTION()
	void OnClickButtonTHigh();

	UFUNCTION()
	void OnClickButtonTUltra();
	//End Texturas
};
