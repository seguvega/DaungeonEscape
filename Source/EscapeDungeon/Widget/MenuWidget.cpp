
#include "MenuWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

bool UMenuWidget::Initialize()
{
	bool FatherSuccess = Super::Initialize();

	(!Button_Jugar ? FatherSuccess = false : FatherSuccess);
	Button_Jugar->OnClicked.AddDynamic(this, &UMenuWidget::OnClickJugar);

	(!Button_Opciones ? FatherSuccess = false : FatherSuccess);
	Button_Opciones->OnClicked.AddDynamic(this, &UMenuWidget::OnClickOpciones);

	(!Button_ComoJugar ? FatherSuccess = false : FatherSuccess);
	Button_ComoJugar->OnClicked.AddDynamic(this, &UMenuWidget::OnClickComoJugar);

	(!Button_Atras ? FatherSuccess = false : FatherSuccess);
	Button_Atras->OnClicked.AddDynamic(this, &UMenuWidget::OnClickAtras);

	(!Button_Salir ? FatherSuccess = false : FatherSuccess);
	Button_Salir->OnClicked.AddDynamic(this, &UMenuWidget::OnClickSalir);

	(!Button_Atras_Opciones ? FatherSuccess = false : FatherSuccess);
	Button_Atras_Opciones->OnClicked.AddDynamic(this, &UMenuWidget::OnClickAtrasOpciones);

	//Botones Config
	//Resolucion
	(!ButtonR720 ? FatherSuccess = false : FatherSuccess);
	ButtonR720->OnClicked.AddDynamic(this, &UMenuWidget::OnclickButtonR720);
	
	(!ButtonR1280 ? FatherSuccess = false : FatherSuccess);
	ButtonR1280->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonR1280);

	(!ButtonR1920 ? FatherSuccess = false : FatherSuccess);
	ButtonR1920->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonR1920);
	
	(!ButtonR2560 ? FatherSuccess = false : FatherSuccess);
	ButtonR2560->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonR2560);

	//Distancia de Dibujado
	(!ButtonVDCerca ? FatherSuccess = false : FatherSuccess);
	ButtonVDCerca->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonVDCerca);

	(!ButtonVDMedio ? FatherSuccess = false : FatherSuccess);
	ButtonVDMedio->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonVDMedio);

	(!ButtonVDLejos ? FatherSuccess = false : FatherSuccess);
	ButtonVDLejos->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonVDLejos);

	//AntiAliasing
	(!ButtonAALow ? FatherSuccess = false : FatherSuccess);
	ButtonAALow->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonAALow);

	(!ButtonAAMed ? FatherSuccess = false : FatherSuccess);
	ButtonAAMed->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonAAMed);
	
	(!ButtonAAHigh ? FatherSuccess = false : FatherSuccess);
	ButtonAAHigh->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonAAHigh);

	(!ButtonAAUltra ? FatherSuccess = false : FatherSuccess);
	ButtonAAUltra->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonAAUltra);

	//Sombras
	(!ButtonSLow ? FatherSuccess = false : FatherSuccess);
	ButtonSLow->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonSLow);

	(!ButtonSMed ? FatherSuccess = false : FatherSuccess);
	ButtonSMed->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonSMed);

	(!ButtonSHigh ? FatherSuccess = false : FatherSuccess);
	ButtonSHigh->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonSHigh);

	(!ButtonSUltra ? FatherSuccess = false : FatherSuccess);
	ButtonSUltra->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonSUltra);

	//Texturas
	(!ButtonTLow ? FatherSuccess = false : FatherSuccess);
	ButtonTLow->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonTLow);

	(!ButtonTMed ? FatherSuccess = false : FatherSuccess);
	ButtonTMed->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonTMed);

	(!ButtonTHigh ? FatherSuccess = false : FatherSuccess);
	ButtonTHigh->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonTHigh);

	(!ButtonTUltra ? FatherSuccess = false : FatherSuccess);
	ButtonTUltra->OnClicked.AddDynamic(this, &UMenuWidget::OnClickButtonTUltra);
	return FatherSuccess;
}

void UMenuWidget::OnClickJugar()
{
	if (!MenuInterface) return;
	MenuInterface->Play();
}

void UMenuWidget::OnClickOpciones()
{
	if (!MainWidgetSwitcher) return;
	if (!MenuSettings) return;
	MainWidgetSwitcher->SetActiveWidget(MenuSettings);
}

void UMenuWidget::OnClickComoJugar()
{
	if (!MainWidgetSwitcher) return;
	if (!MenuGeneral || !MenuInstrucciones) return;
	MainWidgetSwitcher->SetActiveWidget(MenuInstrucciones);
}

void UMenuWidget::OnClickAtras()
{
	if (!MainWidgetSwitcher) return;
	if (!MenuGeneral || !MenuInstrucciones) return;
	MainWidgetSwitcher->SetActiveWidget(MenuGeneral);
}

void UMenuWidget::OnClickAtrasOpciones()
{
	if (!MainWidgetSwitcher) return;
	if (!MenuGeneral || !MenuSettings) return;
	MainWidgetSwitcher->SetActiveWidget(MenuGeneral);
}

void UMenuWidget::OnClickSalir()
{
	if (!MenuInterface) return;
	MenuInterface->Exit();
}

///Funciones Botones Configuracion
//Resolución Posible Solution->https://nerivec.github.io/old-ue4-wiki/pages/game-user-settings.html
void UMenuWidget::OnclickButtonR720()
{
	FString NoLoSe = "SetRes 720x480";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "r.ScreenPercentage 70";
	MenuInterface->ExecCommand(NoLoSe);
}

void UMenuWidget::OnClickButtonR1280()
{
	FString NoLoSe = "SetRes 1280x720";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "r.ScreenPercentage 85";
	MenuInterface->ExecCommand(NoLoSe);
}

void UMenuWidget::OnClickButtonR1920()
{
	FString NoLoSe = "SetRes 1920x1080";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "r.ScreenPercentage 100";
	MenuInterface->ExecCommand(NoLoSe);
}

void UMenuWidget::OnClickButtonR2560()
{
	FString NoLoSe = "SetRes 2560x1440";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "r.ScreenPercentage 100";
	MenuInterface->ExecCommand(NoLoSe);
}


//Distancia de Dibujado
void UMenuWidget::OnClickButtonVDCerca()
{
	FString NoLoSe = "r.ViewDistanceScale 0.4";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "sg.ViewDistanceQuality 0";
	MenuInterface->ExecCommand(NoLoSe);
}

void UMenuWidget::OnClickButtonVDMedio()
{
	FString NoLoSe = "r.ViewDistanceScale 0.7";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "sg.ViewDistanceQuality 2";
	MenuInterface->ExecCommand(NoLoSe);
}

void UMenuWidget::OnClickButtonVDLejos()
{
	FString NoLoSe = "r.ViewDistanceScale 1";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "sg.ViewDistanceQuality 3";
	MenuInterface->ExecCommand(NoLoSe);
}

//AntiAliasing
void UMenuWidget::OnClickButtonAALow()
{
	FString NoLoSe = "r.PostProcessAAQuality 0";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "sg.AntiAliasingQuality 0";
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "sg.PostProcessQuality 0";
	MenuInterface->ExecCommand(NoLoSe);
}

void UMenuWidget::OnClickButtonAAMed()
{
	FString NoLoSe = "r.PostProcessAAQuality 2";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "sg.AntiAliasingQuality 1";
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "sg.PostProcessQuality 1";
	MenuInterface->ExecCommand(NoLoSe);
}

void UMenuWidget::OnClickButtonAAHigh()
{
	FString NoLoSe = "r.PostProcessAAQuality 4";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "sg.AntiAliasingQuality 2";
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "sg.PostProcessQuality 2";
	MenuInterface->ExecCommand(NoLoSe);
}

void UMenuWidget::OnClickButtonAAUltra()
{
	FString NoLoSe = "r.PostProcessAAQuality 6";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "sg.AntiAliasingQuality 3";
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "sg.PostProcessQuality 3";
	MenuInterface->ExecCommand(NoLoSe);
}

//Sombras
void UMenuWidget::OnClickButtonSLow()
{
	FString NoLoSe = "sg.ShadowQuality 0";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "sg.EffectsQuality 0";
	MenuInterface->ExecCommand(NoLoSe);
}

void UMenuWidget::OnClickButtonSMed()
{
	FString NoLoSe = "sg.ShadowQuality 1";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "sg.EffectsQuality 1";
	MenuInterface->ExecCommand(NoLoSe);
}

void UMenuWidget::OnClickButtonSHigh()
{
	FString NoLoSe = "sg.ShadowQuality 2";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "sg.EffectsQuality 2";
	MenuInterface->ExecCommand(NoLoSe);
}

void UMenuWidget::OnClickButtonSUltra()
{
	FString NoLoSe = "sg.ShadowQuality 3";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "sg.EffectsQuality 3";
	MenuInterface->ExecCommand(NoLoSe);
}

//Texturas
void UMenuWidget::OnClickButtonTLow()
{
	FString NoLoSe = "sg.TextureQuality 0";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "r.DetailMode 0";
	MenuInterface->ExecCommand(NoLoSe);
}

void UMenuWidget::OnClickButtonTMed()
{
	FString NoLoSe = "sg.TextureQuality 1";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "r.DetailMode 1";
	MenuInterface->ExecCommand(NoLoSe);
}

void UMenuWidget::OnClickButtonTHigh()
{
	FString NoLoSe = "sg.TextureQuality 2";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "r.DetailMode 2";
	MenuInterface->ExecCommand(NoLoSe);
}

void UMenuWidget::OnClickButtonTUltra()
{
	FString NoLoSe = "sg.TextureQuality 3";
	if (!MenuInterface) return;
	MenuInterface->ExecCommand(NoLoSe);
	NoLoSe = "r.DetailMode 2";
	MenuInterface->ExecCommand(NoLoSe);
}