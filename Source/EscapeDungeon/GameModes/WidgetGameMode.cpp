#include "WidgetGameMode.h"
#include "UObject/ConstructorHelpers.h"

AWidgetGameMode::AWidgetGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> CameraPawn(TEXT("/Game/Blueprints/WidgetPawn/WidgetPawn"));
	if (CameraPawn.Class)
	{
		DefaultPawnClass = CameraPawn.Class;
	}
	else
	{
		DefaultPawnClass = NULL;
	}

}