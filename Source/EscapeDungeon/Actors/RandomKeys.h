// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomKeys.generated.h"

UCLASS()
class ESCAPEDUNGEON_API ARandomKeys : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	int32 NumOfKeys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (MakeEditWidget = "true"))
	TArray<FVector> AllKeysPositions;

	ARandomKeys();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	bool IsValidArray;

	UClass* Key;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RandomizeKeys();
};