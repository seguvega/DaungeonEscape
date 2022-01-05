#pragma once

#include "CoreMinimal.h"
#include "EscapeDungeon/Actors/FatherDoor.h"
#include "ChildDoorLevel1.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class AFatherDoor;

UCLASS()
class ESCAPEDUNGEON_API AChildDoorLevel1 : public AFatherDoor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Componentes")
	UStaticMeshComponent* Placa;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Componentes")
	UBoxComponent* PlacaCollision;

protected:
	bool Aplastado;

	AChildDoorLevel1();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPlacaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlacaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	AActor* TriggerActor;

};
