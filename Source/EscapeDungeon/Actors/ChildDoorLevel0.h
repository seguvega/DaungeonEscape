// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeDungeon/Actors/FatherDoor.h"
#include "ChildDoorLevel0.generated.h"

UCLASS()
class ESCAPEDUNGEON_API AChildDoorLevel0 : public AFatherDoor
{
	GENERATED_BODY()
public:

private:
	AChildDoorLevel0();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
