// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EscapeDungeon/Actors/FatherDoor.h"
#include "ChildDoorWithKeys.generated.h"

class AFarherDoor;
class UStaticMeshComponent;

UCLASS()
class ESCAPEDUNGEON_API AChildDoorWithKeys : public AFatherDoor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Componentes")
	UStaticMeshComponent* OtherPuertaMesh;

	// Sets default values for this actor's properties
	AChildDoorWithKeys();

	void SetBothDoorMovement(bool Move = true);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
