// Fill out your copyright notice in the Description page of Project Settings.


#include "Gargola.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "EscapeDungeon/EscapeDungeonCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGargola::AGargola()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Componente Escena"));
	if (!SceneComponent) return;
	RootComponent = SceneComponent;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Componente De Colisión"));
	if (!BoxComponent) return;
	BoxComponent->SetupAttachment(RootComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGargola::OnBoxComponentOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AGargola::OnBoxComponentEndOverlap);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Compoenente Mesh"));
	if (!MeshComponent) return;
	MeshComponent->SetupAttachment(RootComponent);

	bPlayerIsInRange = false;

}

// Called when the game starts or when spawned
void AGargola::BeginPlay()
{
	Super::BeginPlay();
	GameCharacter = Cast<AEscapeDungeonCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (!GameCharacter) return;
	UE_LOG(LogTemp, Warning, TEXT("Xd -> %s"), *GameCharacter->GetName());
}

// Called every frame
void AGargola::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bPlayerIsInRange)
	{
		FVector PlayerLocation = GameCharacter->GetActorLocation();
		//FRotator NewRot = UKismetMathLibrary::FindLookAtRotation(MeshComponent->GetComponentLocation(), PlayerLocation);
		FRotator NewRot = (PlayerLocation - MeshComponent->GetComponentLocation()).Rotation();//World location = MeshComponent->GetComponentLocation()
		NewRot.Roll = 0;
		NewRot.Pitch = 0;
		NewRot.Yaw += 245.f;//Relativa 245.f; Para que vea de frente ojo NewRot es WorldRotation
		FRotator InterpRot = FMath::RInterpTo(MeshComponent->GetComponentRotation(), NewRot, DeltaTime, 3 * DeltaTime);
		MeshComponent->SetWorldRotation(InterpRot);
	}
}

void AGargola::OnBoxComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GameCharacter == OtherActor)
	{
		bPlayerIsInRange = true;
		UE_LOG(LogTemp, Warning, TEXT("Overlap -> %s"), *OtherActor->GetName());
	}
}

void AGargola::OnBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GameCharacter == OtherActor)
	{
		bPlayerIsInRange = false;
		UE_LOG(LogTemp, Warning, TEXT("EndOverlap -> %s"), *OtherActor->GetName());
	}
}
