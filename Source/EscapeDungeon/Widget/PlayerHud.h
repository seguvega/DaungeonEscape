#pragma once

#include "CoreMinimal.h"
#include "EscapeDungeon/Widget/FatherWidget.h"
#include "PlayerHud.generated.h"

class UFatherWidget;
class UTextBlock;
class UImage;

UCLASS()
class ESCAPEDUNGEON_API UPlayerHud : public UFatherWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_Llaves;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_Fps;

	UPROPERTY(meta = (BindWidget))
	UImage* NotGrab;

	UPROPERTY(meta = (BindWidget))
	UImage* IsGrab;

	void SetText(FString Keys);

	void SetVisibleImage(bool IsGrabbing);

	void SetFps(FString FpsString);

protected:
	virtual bool Initialize() override;

};
