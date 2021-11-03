// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FatherDoor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USceneComponent;
class UTextRenderComponent;

UCLASS()
class ESCAPEDUNGEON_API AFatherDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFatherDoor();

	UPROPERTY(EditAnywhere, Category = "Componentes")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category ="Componentes")
	UBoxComponent* ColisionComponent;

	UPROPERTY(EditAnywhere, Category = "Componentes")
	UStaticMeshComponent* PuertaMesh;

	UPROPERTY(EditAnywhere, Category = "Componentes")
	UTextRenderComponent* MensajeAyuda;

	void SetDoorText(FString Texto);

protected:
	FString PuertaHelp;

	bool IsOpen;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoverPuerta(float Grados, float DeltaTime);

private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
