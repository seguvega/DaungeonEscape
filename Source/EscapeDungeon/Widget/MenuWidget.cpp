
#include "MenuWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

bool UMenuWidget::Initialize()
{
	bool FatherSuccess = Super::Initialize();

	(!Button_Jugar ? FatherSuccess = false : FatherSuccess);
	Button_Jugar->OnClicked.AddDynamic(this, &UMenuWidget::OnClickJugar);
	(!Button_ComoJugar ? FatherSuccess = false : FatherSuccess);
	Button_ComoJugar->OnClicked.AddDynamic(this, &UMenuWidget::OnClickComoJugar);
	(!Button_Atras ? FatherSuccess = false : FatherSuccess);
	Button_Atras->OnClicked.AddDynamic(this, &UMenuWidget::OnClickAtras);
	(!Button_Salir ? FatherSuccess = false : FatherSuccess);
	Button_Salir->OnClicked.AddDynamic(this, &UMenuWidget::OnClickSalir);

	return FatherSuccess;
}

void UMenuWidget::OnClickJugar()
{
	if (!MenuInterface) return;
	MenuInterface->Play();
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

void UMenuWidget::OnClickSalir()
{
	if (!MenuInterface) return;
	MenuInterface->Exit();
}
