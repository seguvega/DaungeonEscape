#include "EscapeDungeon/Actors/FatherDoor.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"//Para el UTextRenderComponent

// Sets default values
AFatherDoor::AFatherDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Componente Escena"));
	if (!SceneComponent) return;
	RootComponent = SceneComponent;

	ColisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Componente Colision"));
	if (!ColisionComponent) return;
	ColisionComponent->SetupAttachment(RootComponent);
	
	PuertaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Componente Mesh"));
	if (PuertaMesh == nullptr) return;
	PuertaMesh->SetupAttachment(RootComponent);

	MensajeAyuda = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Componente Texto"));
	if (!MensajeAyuda) return;
	MensajeAyuda->SetupAttachment(ColisionComponent);
	MensajeAyuda->SetTextRenderColor(FColor::White);
	MensajeAyuda->SetText(FText::FromString(""));

	ColisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFatherDoor::BeginOverlap);
	ColisionComponent->OnComponentEndOverlap.AddDynamic(this, &AFatherDoor::EndOverlap);

	PuertaHelp = "Cambiar el Texto En el Child";
	IsOpen = false;
}

// Called when the game starts or when spawned
void AFatherDoor::BeginPlay()
{
	Super::BeginPlay();
}

void AFatherDoor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("El actor %s me chocó"), *OtherActor->GetName());
	SetDoorText(PuertaHelp);
}

void AFatherDoor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("El actor %s salió"), *OtherActor->GetName());
	SetDoorText(" ");
}

void AFatherDoor::SetDoorText(FString Texto)
{
	FText TransformText = FText::FromString(Texto);
	MensajeAyuda->SetText(TransformText);
}

void AFatherDoor::SetDoorMovement(bool bDoor)
{
	IsOpen = bDoor;
}

void AFatherDoor::MoverPuerta(float Grados, float DeltaTime)
{
	float GradosLentos = FMath::FInterpTo(PuertaMesh->GetRelativeRotation().Yaw, Grados, DeltaTime, 10.f * DeltaTime); //Tiempo tiene q ser > para q sea mas rapido y alrevez para q sea menor
	PuertaMesh->SetRelativeRotation(FRotator(0.f, GradosLentos, 0.f));
}

// Called every frame
void AFatherDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsOpen)
	{
		if (PuertaMesh->GetRelativeRotation().Yaw <= -88.f) return;
		//UE_LOG(LogTemp, Warning, TEXT("Yaw -> %f"), PuertaMesh->GetRelativeRotation().Yaw);
		MoverPuerta(-90.f, DeltaTime);
	}
	else
	{
		if (PuertaMesh->GetRelativeRotation().Yaw >= -1.f) return;
		MoverPuerta(0.f, DeltaTime);
	}
}