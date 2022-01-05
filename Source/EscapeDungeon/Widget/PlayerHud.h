#pragma once

#include "CoreMinimal.h"
#include "EscapeDungeon/Widget/FatherWidget.h"
#include "PlayerHud.generated.h"

class UFatherWidget;
class UTextBlock;

UCLASS()
class ESCAPEDUNGEON_API UPlayerHud : public UFatherWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_Llaves;

	void SetText(FString Keys);

protected:
	virtual bool Initialize() override;
	
};
