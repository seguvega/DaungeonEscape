#pragma once

#include "CoreMinimal.h"
#include "EscapeDungeon/Actors/FatherDoor.h"
#include "ChildDoorLevel2.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class AFatherDoor;

UCLASS()
class ESCAPEDUNGEON_API AChildDoorLevel2 : public AFatherDoor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Componentes")
	UStaticMeshComponent* Baul;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Componentes")
	UBoxComponent* BaulCollision;

protected:
	int32 IntNum;

	int32 NumOfActors;

	AChildDoorLevel2();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//Father Override
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION()
	void OnBaulBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnBaulEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
