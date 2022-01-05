#include "ChildDoorWithKeys.h"
#include "Components/StaticMeshComponent.h"

AChildDoorWithKeys::AChildDoorWithKeys()
{
	OtherPuertaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Componente Mesh Other"));
	if (!OtherPuertaMesh) return;
	OtherPuertaMesh->SetupAttachment(RootComponent);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AChildDoorWithKeys::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AChildDoorWithKeys::BeginPlay()
{
	Super::BeginPlay();
	PuertaHelp = "Consigue las LLaves";
}

void AChildDoorWithKeys::SetBothDoorMovement(bool Move)
{
	PuertaHelp = "OjO";
	SetDoorMovement(Move);
}

void AChildDoorWithKeys::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsOpen)
	{
		float RotatorZ = FMath::FInterpTo(OtherPuertaMesh->GetRelativeRotation().Yaw, 90.f, DeltaTime, 10*DeltaTime);
		OtherPuertaMesh->SetRelativeRotation(FRotator(0.f,RotatorZ, 0.f));
	}
}