// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomKeys.h"
#include "UObject/ConstructorHelpers.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ARandomKeys::ARandomKeys()
{
	///Para encontrar un BP se utiliza la clase del objecto UBlueprint la cual es -> UClass
	static ConstructorHelpers::FObjectFinder<UClass> ActorKey(TEXT("Class '/Game/MedievalDungeon/Blueprints/BP_Key.BP_Key_C'"));
	if (! ActorKey.Object)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error BP_key"));
		return;
	}
	//Se utiliza una TSoftClassPtr<UClass> para conseguir el UClass  el cual es la clase especifica para el BP_Key
	Key = ActorKey.Object;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsValidArray = false;
	NumOfKeys = 3;
}

// Called when the game starts or when spawned
void ARandomKeys::BeginPlay()
{
	Super::BeginPlay();
	if (AllKeysPositions.Num()== 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No tiene elementos el TArray"));
	}
	else
	{
		IsValidArray = true;
		RandomizeKeys();
	}
}

void ARandomKeys::RandomizeKeys()
{
	if (!IsValidArray) return;
	TArray<int32> NoSamePos;
	for (int32 i = 0; i < NumOfKeys; i++)
	{
		int32 Rand = FMath::RandHelper(AllKeysPositions.Num());
		if (NoSamePos.Num() > 0 && NoSamePos.Find(Rand) != INDEX_NONE)
		{
			i--;
		}
		else
		{
			NoSamePos.Add(Rand);
			UE_LOG(LogTemp, Warning, TEXT("Numeros Random -> %i"), NoSamePos[i]);
		}
	}

	for (int32 KeyPos : NoSamePos)
	{
		FVector WorldPos =  GetActorRotation().RotateVector(AllKeysPositions[KeyPos]);
		GetWorld()->SpawnActor<AActor>(Key, WorldPos, FRotator(0.f,0.f,0.f));
		UE_LOG(LogTemp, Warning, TEXT("World Position  -> %s"), *WorldPos.ToString());
	}
	
}

// Called every frame
void ARandomKeys::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}