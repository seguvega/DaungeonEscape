#include "LevelEnd.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "EscapeDungeon/EscapeDungeonCharacter.h"
#include "EscapeDungeon/GameInstance/DungeonGameInstance.h"

ALevelEnd::ALevelEnd()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Componente Escena"));
	if (!SceneComponent) return;
	RootComponent = SceneComponent;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Componente Colisión"));
	if (!CollisionComponent) return;
	CollisionComponent->SetupAttachment(RootComponent);

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Componente Texto"));
	if (!TextRender) return;
	TextRender->SetupAttachment(RootComponent);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ALevelEnd::OnComponentOverlap);
}

void ALevelEnd::OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OverlapPerra -> %s"), *OtherActor->GetName());
	AEscapeDungeonCharacter* TempCharacter = Cast<AEscapeDungeonCharacter>(OtherActor);
	if (TempCharacter)
	{
		UDungeonGameInstance* TempGameInstance = Cast<UDungeonGameInstance>(TempCharacter->GetController()->GetGameInstance());
		if (TempGameInstance)
		{
			TempGameInstance->EndGame();
		}
	}
}


void ALevelEnd::BeginPlay()
{
	Super::BeginPlay();
	if (!TextRender) return;
	TextRender->SetText("Gracias por Jugar :)");
}


void ALevelEnd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}