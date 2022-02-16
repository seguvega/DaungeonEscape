#include "LevelEnd.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "EscapeDungeon/EscapeDungeonCharacter.h"
#include "EscapeDungeon/GameInstance/DungeonGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	IsOverlap = false;
	TimeinSeconds = 0.f;
	MaxWaitTime = 5.f;
}

void ALevelEnd::OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IsOverlap = true;
	AEscapeDungeonCharacter* TempCharacter = Cast<AEscapeDungeonCharacter>(OtherActor);
	if (TempCharacter)
	{
		Character = TempCharacter;
		TempCharacter->GetCharacterMovement()->DisableMovement();
		RenderCreditos();
	}
}


void ALevelEnd::BeginPlay()
{
	Super::BeginPlay();
	if (!TextRender) return;
	Creditos.Add("Gracias por Jugar!!!");
	Creditos.Add("Creado por: \n Sebastian Velasco \n Kevin Ramirez");
	Creditos.Add("Creditos: \n Iconos");
	Creditos.Add("Retornando al Menu ... =)");
}

void ALevelEnd::RenderCreditos()
{
	if (Creditos.Num() >= 1)
	{
		TextRender->SetText(Creditos[0]);
		Creditos.RemoveAt(0);
	}
}

void ALevelEnd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsOverlap)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tiempo -> %f"), TimeinSeconds);
		TimeinSeconds += DeltaTime;
		if (TimeinSeconds >= MaxWaitTime && Creditos.Num() > 0)
		{
			RenderCreditos();
			TimeinSeconds = 0;
		}
		if (TimeinSeconds > MaxWaitTime)
		{
			IsOverlap = false;
			if (Character)
			{
				UDungeonGameInstance* TempGameInstance = Cast<UDungeonGameInstance>(Character->GetController()->GetGameInstance());
				if (TempGameInstance)
				{
					TempGameInstance->EndGame();
				}
			}
		}
	}
}