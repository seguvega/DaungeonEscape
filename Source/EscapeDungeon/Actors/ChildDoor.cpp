#include "ChildDoor.h"

// Sets default values
AChildDoor::AChildDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AChildDoor::BeginPlay()
{
	Super::BeginPlay();
	PuertaHelp = "Consigue este Objeto";
	MeshLocation = PuertaMesh->GetRelativeLocation();
}

//Edito la funcion MoverPuerta del padre
void AChildDoor::MoverPuerta(float Grados, float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("Hijo -> %s ///// Grados: %f"), *PuertaHelp, Grados);
	float PosicionZ = FMath::FInterpTo(PuertaMesh->GetRelativeLocation().Z, MeshLocation.Z + 200.f , DeltaTime, 10.f * DeltaTime);
	FVector TemLocation = PuertaMesh->GetRelativeLocation();
	TemLocation.Z = PosicionZ;
	PuertaMesh->SetRelativeLocation(TemLocation);
}

// Called every frame
void AChildDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}