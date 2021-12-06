// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EscapeDungeonCharacter.generated.h"

class USpringArmComponent;
class UPhysicsHandleComponent;
class UPrimitiveComponent;
class UDungeonGameInstance;

UCLASS(config=Game)
class AEscapeDungeonCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	///Agarrar Objetos 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPhysicsHandleComponent* PhysicsHandle;

public:
	AEscapeDungeonCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agarre")
	float ArmLength;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	///Funciones de para los Inputs
	void MenuPausa();

	void Rodar();

	void AgarrarSoltar();
	///End Inputs

	///Desplegar el Widget
	void CrearMenu();

	void DestruirMenu();
	///End Desplegar el Widget

	///Agarrar Objetos 
	void Agarrar();

	void Soltar();

	void AgregarFisicas(UPrimitiveComponent* ActorAgarrado, FVector ActorLocation);
	///End Agarrar Objetos 

private:
	///Desplegar el Widget
	bool IsMenuActive;

	UDungeonGameInstance* MyGameInstance;
	///End Desplegar el Widget
	
	///Agarrar Objetos 
	//Me permite editar las variables Primitivas de un AActor
	UPrimitiveComponent* ActorPrimitiveComponent;

	bool IsGrab;

	UWorld* Mundo;
};