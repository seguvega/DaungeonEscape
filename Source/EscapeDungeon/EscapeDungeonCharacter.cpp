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
#include "Kismet/KismetMathLibrary.h"
#include "EscapeDungeon/GameInstance/DungeonGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "EscapeDungeon/Actors/ChildDoorWithKeys.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

//////////////////////////////////////////////////////////////////////////
// AEscapeDungeonCharacter
AEscapeDungeonCharacter::AEscapeDungeonCharacter()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RollMontageObject (TEXT("/Game/Anim/Rodar/StandToRoll_Montage"));
	if (!RollMontageObject.Object) return;
	RollMontage = RollMontageObject.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> GettingUpObject (TEXT("/Game/Anim/Trepar/MQ_GettingUp_RM_Montage"));
	if (!GettingUpObject.Object) return;
	GettingUp = GettingUpObject.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ClimbObject (TEXT("/Game/Anim/Trepar/MQ_Climb_RM_Montage"));
	if (!ClimbObject.Object) return;
	Climb = ClimbObject.Object;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(48.f, 82.0f);

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
	ArmLength = 200.f;
	LlavesAgarradas = 0.f;
	IsGrab = false;
	IsMenuActive = false;
	NumOfRolls = 0;
	bIsRolling = false;
	bCanClimb = false;
	bTrepar = false;
	bEscalar = false;
	IsPlayAnyClimbAnim = false;
}

void AEscapeDungeonCharacter::BeginPlay()
{
	Super::BeginPlay();
	Mundo = GetWorld();
	if (!Mundo) return;

	MyGameInstance = Cast<UDungeonGameInstance>(GetGameInstance());
	if (!MyGameInstance) return;

	if (!RollMontage) return;
	// BindEndAnimationMotage
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &AEscapeDungeonCharacter::OnMontageEnded);

	//Despliego el HUD
	MyGameInstance->CreatePlayerHud();
}

//////////////////////////////////////////////////////////////////////////
// Input
void AEscapeDungeonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AEscapeDungeonCharacter::Jump);
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
	if (NumOfRolls < 5)
	{
		NumOfRolls++;
	}
}

void AEscapeDungeonCharacter::Jump()
{
	if (bIsRolling) return;
	FVector Start = GetActorLocation();
	Start.Z += 28.f;
	FVector End = Start + GetActorForwardVector() * 150.f;
	TArray<TEnumAsByte<EObjectTypeQuery>> Array;
	Array.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	FHitResult HitResult;
	if (UKismetSystemLibrary::LineTraceSingleForObjects(Mundo, Start, End, Array, true, IgnoreActors, EDrawDebugTrace::None, HitResult, true))
	{
		if (HitResult.IsValidBlockingHit())
		{
			WallLocation = HitResult.Location;
			WallNormal = HitResult.Normal;
			///Para Localizar la altura del Objeto
			// GetForwardVector Retorna el vector en X o Y Pero este esta aputando al jugador!!!
			FVector TempWallLocation = WallLocation + UKismetMathLibrary::GetForwardVector(WallNormal.Rotation()) * -10.F;//location + Direccion * Magnitud y sentido
			FVector WallStart = FVector(TempWallLocation.X, TempWallLocation.Y, TempWallLocation.Z + 200);//Punto muy Arriba en Z
			FVector WallEnd = FVector(WallStart.X, WallStart.Y, WallStart.Z - 200.f);//Es el punto del ventor TempWallLocation
			FHitResult HeightHit;
			if (UKismetSystemLibrary::LineTraceSingleForObjects(Mundo, WallStart, WallEnd, Array, true, IgnoreActors, EDrawDebugTrace::None, HeightHit, true))
			{
				if (HeightHit.IsValidBlockingHit() && !bCanClimb && !IsPlayAnyClimbAnim)
				{
					WallHeight = HeightHit.Location;
					FVector Altura = WallHeight - WallLocation;
					UE_LOG(LogTemp, Warning, TEXT("Altura del Objeto %s ->"), *Altura.ToString());
					bCanClimb = true;
					if (Altura.Z <= 20 && !bTrepar)
					{
						bTrepar = true;
						return;
					}
					if (Altura.Z > 20 && !bEscalar)
					{
						GetCharacterMovement()->DisableMovement();
						bEscalar = true;
						return;
					}
				}
			}
			else
			{
				//Si la segunda linea de verificacion no choca salto
				ACharacter::Jump();
			}
		}
	}
	else
	{
		ACharacter::Jump();
	}
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
	if (UKismetSystemLibrary::SphereTraceSingle(Mundo, StartPoint, EndPoint, 25.f, MyQuery, false, ActorsToIgnore, EDrawDebugTrace::Type::ForDuration, HitResult, true))
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
							AgregarFisicas(HitResult.GetComponent(), HitResult.Location);
						}
						else if (Tag.IsEqual(FName("Llave")))
						{
							IsGrab = false;
							if (LlavesAgarradas < 3)//Block in 3
							{
								LlavesAgarradas++;
								HitResult.Actor->Destroy();
								MyGameInstance->SendKeys(FString::FromInt(LlavesAgarradas));
								if (LlavesAgarradas == 3)
								{
									//Encuentro el objeto que pertenece a la clase AChildDoorWithKeys
									TArray<AActor*> FoundActors;
									TSubclassOf<AChildDoorWithKeys> ClassToFind = AChildDoorWithKeys::StaticClass();
									UGameplayStatics::GetAllActorsOfClass(Mundo, ClassToFind, FoundActors);
									if (FoundActors.Num() > 0)
									{
										AChildDoorWithKeys* TempActor = Cast<AChildDoorWithKeys>(FoundActors[0]);
										if (TempActor)
										{
											TempActor->SetBothDoorMovement();
										}
									}
								}
							}
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
	//Comparo Si volvio a Agarrar el mismo Actor q soltó
	if (ActorsToDisassembleFisics.Num() > 0 && ActorsToDisassembleFisics.Contains(ActorAgarrado))
	{
		//No Le agarro si ya esta en el array IsGrab = false
		IsGrab = false;
		UE_LOG(LogTemp, Warning, TEXT("Agarraste el mismo wey >:V"));
		return;
	
	}
	ActorPrimitiveComponent = ActorAgarrado;
	if (!ActorPrimitiveComponent) return;
	//Configuro al Actor como Movible
	ActorPrimitiveComponent->SetMobility(EComponentMobility::Movable);
	//Configuro el evento Overlap
	ActorPrimitiveComponent->SetGenerateOverlapEvents(true);
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
	//Libero el componente
	PhysicsHandle->ReleaseComponent();

	if (!ActorPrimitiveComponent) return;
	//Guardo El PrimitiveComponent
	ActorsToDisassembleFisics.Add(ActorPrimitiveComponent);
	IsGrab = false;

	//Activo el Colission Preset para Bloquear las colisiones BlockAll
	ActorPrimitiveComponent->SetCollisionProfileName(FName("BlockAll"));
	//Desbloqueo la rotación
	ActorPrimitiveComponent->GetBodyInstance()->bLockYRotation = false;
	ActorPrimitiveComponent->GetBodyInstance()->bLockZRotation = false;
	ActorPrimitiveComponent->GetBodyInstance()->bLockXRotation = false;
	ActorPrimitiveComponent->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);

	///Delay para desactivar las fisicas
	///OjO que si coges el mismo objeto enseguida se queda estatico por el timer
	FTimerHandle TempHandle;
	Mundo->GetTimerManager().SetTimer(TempHandle, this, &AEscapeDungeonCharacter::DesactivarFisicas, 1.6f, false);
}

void AEscapeDungeonCharacter::DesactivarFisicas()
{
	if (ActorsToDisassembleFisics.Num() > 0 )
	{
		UE_LOG(LogTemp, Warning, TEXT("Tamaño Antes array -> %i"), ActorsToDisassembleFisics.Num());
		
		//Equals --> if (!ActorsToDisassembleFisics[0]) return; aunq el check crashea el juego si el puntero no es valido
		check(ActorsToDisassembleFisics[0]);
		//Desactivo las Fisicas 
		ActorsToDisassembleFisics[0]->SetSimulatePhysics(false);

		//Configuro al Actor como Static
		ActorsToDisassembleFisics[0]->SetMobility(EComponentMobility::Static);

		//Siempre remuevo el Primer valor q entró
		ActorsToDisassembleFisics.RemoveAt(0);

		UE_LOG(LogTemp, Warning, TEXT("Tamaño despues array -> %i"), ActorsToDisassembleFisics.Num());
	}
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
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	MyGameInstance->RestartInputMode();
}

void AEscapeDungeonCharacter::SetupCharacterToRoll(bool StartRolling)
{
	UCapsuleComponent* TempCapsuleComponent = GetCapsuleComponent();
	float Height = TempCapsuleComponent->GetUnscaledCapsuleHalfHeight();
	float Radius = TempCapsuleComponent->GetUnscaledCapsuleRadius();
	FVector TempMeshLocation = GetMesh()->GetRelativeLocation();
	if (StartRolling)
	{
		TempMeshLocation.Z += 30.f;
		Height /= 2;
	}
	else
	{
		TempMeshLocation.Z -= 30.f;
		Height *= 2;
	}
	TempCapsuleComponent->SetCapsuleSize(Radius, Height);
	GetMesh()->SetRelativeLocation(TempMeshLocation);
}

void AEscapeDungeonCharacter::SetupCharacterToClimb(bool StartClimbing)
{
	if (StartClimbing)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		FVector NewPos = GetActorLocation() + UKismetMathLibrary::GetForwardVector(WallNormal.Rotation()) + 20.f;
		FRotator NewRot = WallNormal.Rotation();
		NewRot.Yaw += 180;
		FRotator ActorRot = GetActorRotation();
		FQuat NewActorRot = FRotator(ActorRot.Pitch, NewRot.Yaw, ActorRot.Roll).Quaternion();
		SetActorLocationAndRotation(NewPos, NewActorRot);
	}
	else
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		FRotator Direccion = WallNormal.Rotation();
		Direccion.Yaw += 180;
		FRotator TempRotacion = GetActorRotation();
		FQuat NewRotation = FRotator(TempRotacion.Pitch, Direccion.Yaw, TempRotacion.Roll).Quaternion();
		SetActorRotation(NewRotation);
	}
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
		FVector TempFinalPoint = TempBoneLocation + TempCameraRotation.Vector() * (ArmLength);

		//Rotacion del Personaje
		//FVector TempFinalPoint = TempBoneLocation + GetActorForwardVector() * 2.f;
		PhysicsHandle->SetTargetLocation(TempFinalPoint);
	}

	if (NumOfRolls > 0 && !bIsRolling && !IsPlayingRootMotion())
	{
		bIsRolling = true;
		SetupCharacterToRoll(true);
		UE_LOG(LogTemp, Warning, TEXT("Character Speed -> %f"), GetCharacterMovement()->GetMaxSpeed());
		PlayAnimMontage(RollMontage);
	}

	if (bCanClimb && !IsPlayingRootMotion())
	{
		bCanClimb = false;
		IsPlayAnyClimbAnim = true;
		if (bTrepar)
		{
			bTrepar = false;
			SetupCharacterToClimb(true);
			PlayAnimMontage(GettingUp);
		}
		else if (bEscalar)
		{
			bEscalar = false;
			SetupCharacterToClimb(true);
			PlayAnimMontage(Climb);
		}
	}
}

void AEscapeDungeonCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == RollMontage && NumOfRolls > 0)
	{
		bIsRolling = false;
		SetupCharacterToRoll(false);
		NumOfRolls--;
	}
	if (Montage == GettingUp)
	{
		IsPlayAnyClimbAnim = false;
		bCanClimb = false;
		SetupCharacterToClimb(false);
	}
	if (Montage == Climb)
	{
		IsPlayAnyClimbAnim = false;
		bCanClimb = false;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		SetupCharacterToClimb(false);
	}
}