#include "ChildDoor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SceneComponent.h"
#include "Engine/StaticMeshActor.h"

// Sets default values
AChildDoor::AChildDoor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ActorObject(TEXT("/Game/MedievalDungeon/Meshes/Props/SM_Gargoyle_Statue"));
	if (!ActorObject.Object) return;
	StaticMeshABuscar = ActorObject.Object;

	ActorPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Componente Guía"));
	if (!ActorPosition) return;
	ActorPosition->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AChildDoor::BeginPlay()
{
	Super::BeginPlay();
	PuertaHelp = "Consigue este Objeto";
	AStaticMeshActor* MeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(ActorPosition->GetComponentLocation(), FRotator(0, 0, 0));
	MeshActor->SetMobility(EComponentMobility::Static);
	MeshActor->GetStaticMeshComponent()->SetStaticMesh(StaticMeshABuscar);
	MeshLocation = PuertaMesh->GetRelativeLocation();
}

void AChildDoor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor->ActorHasTag("End"))
	{
		SetDoorMovement(true);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("NO "));
	}
}

//Edito la funcion MoverPuerta del padre
void AChildDoor::MoverPuerta(float Grados, float DeltaTime)
{
	float PosicionZ = FMath::FInterpTo(PuertaMesh->GetRelativeLocation().Z, MeshLocation.Z + 180.f , DeltaTime, 10.f * DeltaTime);
	FVector TemLocation = PuertaMesh->GetRelativeLocation();
	TemLocation.Z = PosicionZ;
	if ((MeshLocation.Z + 180.f) - TemLocation.Z <= 50.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hijo VFinal -> %f "), TemLocation.Z);
		return;
	}
	PuertaMesh->SetRelativeLocation(TemLocation);
}

// Called every frame
void AChildDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}