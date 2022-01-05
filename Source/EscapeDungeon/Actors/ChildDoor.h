#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EscapeDungeon/Actors/FatherDoor.h"
#include "ChildDoor.generated.h"

class USceneComponent;
class AStaticMeshActor;
class UStaticMesh;

UCLASS()
class ESCAPEDUNGEON_API AChildDoor : public AFatherDoor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChildDoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Componentes")
	USceneComponent* ActorPosition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MoverPuerta(float Grados, float DeltaTime) override; ///Se sobreescribe la funcion del padre

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector MeshLocation;

	UStaticMesh* StaticMeshABuscar;

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
