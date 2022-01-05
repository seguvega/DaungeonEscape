// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gargola.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USceneComponent;
class AEscapeDungeonCharacter;

UCLASS()
class ESCAPEDUNGEON_API AGargola : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGargola();

	bool bPlayerIsInRange;

protected:
	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess))
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess))
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess))
	UStaticMeshComponent* MeshComponent;

	AEscapeDungeonCharacter* GameCharacter;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBoxComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
