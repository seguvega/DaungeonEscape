#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EscapeDungeon/Actors/FatherDoor.h"
#include "ChildDoor.generated.h"

UCLASS()
class ESCAPEDUNGEON_API AChildDoor : public AFatherDoor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChildDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MoverPuerta(float Grados, float DeltaTime) override; ///Se sobreescribe la funcion del padre

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 
	FVector MeshLocation;

};
