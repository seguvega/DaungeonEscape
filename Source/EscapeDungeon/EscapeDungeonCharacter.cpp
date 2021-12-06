// Copyright Epic Games, Inc. All Rights Reserved.

#include "EscapeDungeonCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h" //Dibuja una lineaDebug
#include "Kismet/KismetSystemLibrary.h"
#include "EscapeDungeon/GameInstance/DungeonGameInstance.h"

//////////////////////////////////////////////////////////////////////////
// AEscapeDungeonCharacter
AEscapeDungeonCharacter::AEscapeDungeonCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>("Componente Fisicas");
	if (!PhysicsHandle) return;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Inicializate 
	ArmLength = 300.f;
	IsGrab = false;
	IsMenuActive = false;
}

void AEscapeDungeonCharacter::BeginPlay()
{
	Super::BeginPlay();
	Mundo = GetWorld();
	if (!Mundo) return;

	MyGameInstance = Cast<UDungeonGameInstance>(GetGameInstance());
	if (!MyGameInstance) return;
	//UE_LOG(LogTemp, Warning, TEXT("Vale perro -> %s"), *MyGameInstance->GetName());
}

//////////////////////////////////////////////////////////////////////////
// Input
void AEscapeDungeonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Rodar", IE_Pressed, this, &AEscapeDungeonCharacter::Rodar);
	PlayerInputComponent->BindAction("Agarrar", IE_Pressed, this, &AEscapeDungeonCharacter::AgarrarSoltar);
	PlayerInputComponent->BindAction("AbrirMenu", IE_Pressed, this, &AEscapeDungeonCharacter::MenuPausa);

	PlayerInputComponent->BindAxis("MoveForward", this, &AEscapeDungeonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEscapeDungeonCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AEscapeDungeonCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AEscapeDungeonCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AEscapeDungeonCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AEscapeDungeonCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AEscapeDungeonCharacter::OnResetVR);
}

void AEscapeDungeonCharacter::AgarrarSoltar()
{
	if (!IsGrab)
	{
		Agarrar();
	}
	else
	{
		Soltar();
	}
}

void AEscapeDungeonCharacter::MenuPausa()
{
	if (IsMenuActive)
	{
		DestruirMenu();
	}
	else 
	{
		CrearMenu();
	}
}

void AEscapeDungeonCharacter::Rodar()
{
	UE_LOG(LogTemp, Warning, TEXT("Tecla v presionada!!!!"));
}

void AEscapeDungeonCharacter::OnResetVR()
{
	// If EscapeDungeon is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in EscapeDungeon.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AEscapeDungeonCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AEscapeDungeonCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AEscapeDungeonCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AEscapeDungeonCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AEscapeDungeonCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AEscapeDungeonCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AEscapeDungeonCharacter::Agarrar()
{
	IsGrab = true;
	FHitResult HitResult;
	FVector CameraLocation;
	FRotator CameraRotation;
	GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);
	//Bone Location
	FVector BoneLocation = GetMesh()->GetBoneLocation(FName("Head"));
	///TODO Validar BoneLocation
	FVector StartPoint = BoneLocation + CameraRotation.Vector();
	FVector EndPoint = BoneLocation + CameraRotation.Vector() * ArmLength;//Vector() == Dirección
	// Dibujar una linea Debug -> DrawDebugLine(Mundo, StartPoint, EndPoint, FColor::Red, false, 5.f, 2.f);
	ETraceTypeQuery MyQuery = UEngineTypes::ConvertToTraceType(ECC_Visibility);//Ojito
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	if (UKismetSystemLibrary::SphereTraceSingle(Mundo, StartPoint, EndPoint, 15.f, MyQuery, false, ActorsToIgnore, EDrawDebugTrace::Type::ForDuration, HitResult, true))
	{
		if (HitResult.IsValidBlockingHit())
		{
			if (HitResult.Actor.IsValid())
			{
				TArray<FName> ActorTags = HitResult.Actor->Tags;
				if (ActorTags.Num() > 0)
				{
					for (auto Tag : ActorTags)
					{
						if (Tag.IsEqual(FName("agarrable")))
						{
							UE_LOG(LogTemp, Warning, TEXT("Actor %s si es agarrable"), *HitResult.Actor->GetName());
							AgregarFisicas(HitResult.GetComponent(), HitResult.Location);
						}
					}
				}
				else
				{
					//Si el Actor no tiene ningun tag
					IsGrab = false;
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Actor no Valido (Q raro)"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Hay colision")); //No hagarro nada
		IsGrab = false;
	}
}

void AEscapeDungeonCharacter::AgregarFisicas(UPrimitiveComponent* ActorAgarrado, FVector ActorLocation)
{
	ActorPrimitiveComponent = ActorAgarrado;
	if (!ActorPrimitiveComponent) return;
	//Configuro al Actor como Movible
	ActorPrimitiveComponent->SetMobility(EComponentMobility::Movable);
	//Configuro el Colission Presets
	ActorPrimitiveComponent->SetCollisionProfileName(FName("Agarrable"));
	//Activo las Fisicas
	ActorPrimitiveComponent->SetSimulatePhysics(true);
	//Bloqueo la rotación
	ActorPrimitiveComponent->GetBodyInstance()->bLockYRotation = true;
	ActorPrimitiveComponent->GetBodyInstance()->bLockZRotation= true;
	ActorPrimitiveComponent->GetBodyInstance()->bLockXRotation = true;
	ActorPrimitiveComponent->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);

	PhysicsHandle->GrabComponentAtLocation(ActorPrimitiveComponent, FName("Head"), ActorLocation);
}

void AEscapeDungeonCharacter::Soltar()
{
	IsGrab = false;
	//Libero el componente
	PhysicsHandle->ReleaseComponent();

	if (!ActorPrimitiveComponent) return;
	//Activo el Colission Preset para Bloquear las colisiones BlockAll
	ActorPrimitiveComponent->SetCollisionProfileName(FName("BlockAll"));
	//Desbloqueo la rotación
	ActorPrimitiveComponent->GetBodyInstance()->bLockYRotation = false;
	ActorPrimitiveComponent->GetBodyInstance()->bLockZRotation = false;
	ActorPrimitiveComponent->GetBodyInstance()->bLockXRotation = false;
	ActorPrimitiveComponent->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);
	
	///TODO Hacer un delay para desactivar las fisicas para q se sienta q tira el objeto luego desactivo las fisicas y estatico
	//Desactivo las Fisicas 
	ActorPrimitiveComponent->SetSimulatePhysics(false);

	//Configuro al Actor como Static
	ActorPrimitiveComponent->SetMobility(EComponentMobility::Static);

	//Limpio el puntero ActorPrimitiveComponent
	ActorPrimitiveComponent = nullptr;
}

void AEscapeDungeonCharacter::CrearMenu()
{
	IsMenuActive = true;
	//GetCharacterMovement()->StopMovementImmediately();//TODO Poner en un temporizador
	//UE_LOG(LogTemp, Warning, TEXT("Activo Con movimiento: %s"), *GetCharacterMovement()->GetMovementName());//Walking
	GetCharacterMovement()->DisableMovement();
	/*----------------------------------------------TODO un boton para pausar y reanudar
	APlayerController* TempPlayerController = Cast<APlayerController>(GetController());
	if (TempPlayerController)
	{
		TempPlayerController->SetPause(true);
	}
	*/
	MyGameInstance->CreateInGameMenu();
}

void AEscapeDungeonCharacter::DestruirMenu()
{
	IsMenuActive = false;
	UE_LOG(LogTemp, Warning, TEXT("Desactivado"));
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	MyGameInstance->RestartInputMode();
}

void AEscapeDungeonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PhysicsHandle->GrabbedComponent)
	{
		FVector TempCameraLocation;
		FRotator TempCameraRotation;
		FVector TempBoneLocation = GetMesh()->GetBoneLocation(FName("Head"));
		GetController()->GetPlayerViewPoint(TempCameraLocation, TempCameraRotation);
		//Rotacion de la Camara
		FVector TempFinalPoint = TempBoneLocation + TempCameraRotation.Vector() * (ArmLength/3);

		//Rotacion del Personaje
		//FVector TempFinalPoint = TempBoneLocation + GetActorForwardVector() * 2.f;
		PhysicsHandle->SetTargetLocation(TempFinalPoint);
	}
}