#include "PlayerHud.h"
#include "Components/TextBlock.h"

bool UPlayerHud::Initialize()
{
	bool Success = Super::Initialize();
	(!TB_Llaves ? Success = false : Success = true);
	return Success;
}

void UPlayerHud::SetText(FString Keys)
{
	TB_Llaves->SetText(FText::FromString(Keys));
}
