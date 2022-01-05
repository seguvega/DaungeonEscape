#include "ChildDoorLevel0.h"

AChildDoorLevel0::AChildDoorLevel0()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AChildDoorLevel0::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	IsOpen = true;
}

void AChildDoorLevel0::BeginPlay()
{
	Super::BeginPlay();
	PuertaHelp = "Puerta Automatica";
}

void AChildDoorLevel0::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
