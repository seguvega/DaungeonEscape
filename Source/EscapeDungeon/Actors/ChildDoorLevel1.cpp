#include "ChildDoorLevel1.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

AChildDoorLevel1::AChildDoorLevel1()
{
	Placa = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Placa Mesh"));
	if (!Placa) return;
	Placa->SetupAttachment(RootComponent);
	PlacaCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Placa Colission"));
	if (!PlacaCollision) return;
	PlacaCollision->SetupAttachment(RootComponent);

	PlacaCollision->OnComponentBeginOverlap.AddDynamic(this, &AChildDoorLevel1::OnPlacaBeginOverlap);
	PlacaCollision->OnComponentEndOverlap.AddDynamic(this, &AChildDoorLevel1::OnPlacaEndOverlap);

	PrimaryActorTick.bCanEverTick = true;
	Aplastado = false;
	TriggerActor = nullptr;
}

void AChildDoorLevel1::OnPlacaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Aplastado)
	{
		TriggerActor = OtherActor;
		FVector PlacaPos = Placa->GetComponentLocation();
		PlacaPos.Z = PlacaPos.Z - 8.f;
		Placa->SetWorldLocation(PlacaPos);
		SetDoorMovement(true);
		Aplastado = true;
	}
	
}

void AChildDoorLevel1::OnPlacaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Aplastado && TriggerActor == OtherActor)
	{
		FVector PlacaPos = Placa->GetComponentLocation();
		PlacaPos.Z = PlacaPos.Z + 8.f;
		Placa->SetWorldLocation(PlacaPos);
		SetDoorMovement(false);
		Aplastado = false;
	}
}

void AChildDoorLevel1::BeginPlay()
{
	Super::BeginPlay();
	PuertaHelp = "Presiona la Placa";
}

void AChildDoorLevel1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}