#include "ChildDoorLevel2.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"

AChildDoorLevel2::AChildDoorLevel2()
{
	PrimaryActorTick.bCanEverTick = true;
	Baul = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Baul Mesh"));
	if (!Baul) return;
	Baul->SetupAttachment(RootComponent);
	BaulCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Baul Colission"));
	if (!BaulCollision) return;
	BaulCollision->SetupAttachment(RootComponent);

	BaulCollision->OnComponentBeginOverlap.AddDynamic(this, &AChildDoorLevel2::OnBaulBeginOverlap);
	BaulCollision->OnComponentEndOverlap.AddDynamic(this, &AChildDoorLevel2::OnBaulEndOverlap);
}

void AChildDoorLevel2::OnBaulBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		NumOfActors++;
		if (NumOfActors >= IntNum)
		{
			SetDoorMovement(true);
		}
		else 
		{
			SetDoorMovement(false);
		}
	}
}

void AChildDoorLevel2::OnBaulEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		NumOfActors--;
		if (NumOfActors < IntNum)
		{
			SetDoorMovement(false);
		}
	}
}

void AChildDoorLevel2::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	int32 TempRes = IntNum - NumOfActors;
	if (TempRes <= 0)
	{
		PuertaHelp = "Buenaa :)";
	}
	else
	{
		PuertaHelp = "Te Faltan "+ FString::FromInt(TempRes)+ " Objectos";
	}
	//Primero Cambio PuertaHelp y luego llamo al Padre
	Super::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AChildDoorLevel2::BeginPlay()
{
	Super::BeginPlay();
	float Num = FMath::FRandRange(4.f, 13.f);
	IntNum = FMath::FloorToInt(Num);
	PuertaHelp = "Ingresa " + FString::FromInt(IntNum) + " Objectos";
	UE_LOG(LogTemp, Warning, TEXT("Mi rand -> %i"), IntNum);
}

void AChildDoorLevel2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}