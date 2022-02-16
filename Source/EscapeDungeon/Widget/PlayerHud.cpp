#include "PlayerHud.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

bool UPlayerHud::Initialize()
{
	bool Success = Super::Initialize();
	(!TB_Llaves ? Success = false : Success = true);
	(!NotGrab ? Success = false : Success = true);
	(!IsGrab ? Success = false : Success = true);
	return Success;
}

void UPlayerHud::SetText(FString Keys)
{
	TB_Llaves->SetText(FText::FromString(Keys));
}

void UPlayerHud::SetFps(FString FpsString)
{
	TB_Fps->SetText(FText::FromString(FpsString));
}

void UPlayerHud::SetVisibleImage(bool IsGrabbing)
{
	if (IsGrabbing)
	{
		NotGrab->SetVisibility(ESlateVisibility::Hidden);
		IsGrab->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		IsGrab->SetVisibility(ESlateVisibility::Hidden);
		NotGrab->SetVisibility(ESlateVisibility::Visible);
	}
}