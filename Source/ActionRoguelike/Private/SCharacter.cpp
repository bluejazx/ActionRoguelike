// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "SAttributeComponent.h"


// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates SpringArmComp in 
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	//SpringArmComp use this characters rotation
	SpringArmComp->bUsePawnControlRotation = true;
	//Attaches SpringArmComp to 
	SpringArmComp->SetupAttachment(RootComponent);

	//Creates CameraComp
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	//Attaches CameraComp to SpringArmComp
	CameraComp->SetupAttachment(SpringArmComp);

	//Creates InteractionComp
	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	//Creates AttributeComp
	AttrributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	//Moves in direction this character is facing
	GetCharacterMovement()->bOrientRotationToMovement = true;

	//Allows for RPG(souls-like) camera where player can look into the camera  without changing the direction the player is looking 
	//By rotating to the direction of input
	bUseControllerRotationYaw = false;

	//Sets AttackAnimDelay
	AttackAnimDelay = 0.2f;
}


//Binding Inputs
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Allows SCharacter to move along z axis(forward/back) with W/S 
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	//Allows SCharacter to move along x axis(left/right) with D/A 
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	//Turn this character with Vertical/Horizontal(Yaw/Pitch) mouse inputs
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//Binds PrimaryAttack(left mouse)
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	//Binds SecondaryAttack(Q)
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &ASCharacter::BlackHoleAttack);

	//Binds Dash(E)
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ASCharacter::Dash);

	//Binds Interact(F)
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);

	//Binds Jump(Space)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}



void ASCharacter::MoveForward(float Value)
{
	//Variable for rotation
	FRotator ControlRot = GetControlRotation();
	//Variable for Pitch and Roll
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	//moves in direction along z
	AddMovementInput(ControlRot.Vector(), Value);
}


void ASCharacter::MoveRight(float Value)
{
	//Variable for rotation
	FRotator ControlRot = GetControlRotation();
	//Variable for Pitch and Roll
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// X = Forward (Red)
	// Y = Right (Green)
	// Z = Up (Blue)

	//Sets RightVector to right axis
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	//moves in direction along x
	AddMovementInput(RightVector, Value);
}


//Trigger Primary attack Animation then spawn projectile
void ASCharacter::PrimaryAttack()
{
	//Plays AttackAnim
	PlayAnimMontage(AttackAnim);

	//Sets AttackAnim timer
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);

	//Clears the timer handle if SCharacter dies
	// GetWorldTimerManager().ClearTimer(TimerHanlde_PrimaryAttack);

	
}

//Triggered by PrimaryAttack() once the Primary attack animation is finished after 0.2f and spawns projectile
void ASCharacter::PrimaryAttack_TimeElapsed()
{
	//spawns PrimaryAttack
	SpawnProjectile(ProjectileClass);
}


void ASCharacter::BlackHoleAttack()
{
	//Plays AttackAnim
	PlayAnimMontage(AttackAnim);

	//Sets AttackAnim timer
	GetWorldTimerManager().SetTimer(TimerHandle_BlackholeAttack, this, &ASCharacter::BlackholeAttack_TimeElapsed, AttackAnimDelay);
}


void ASCharacter::BlackholeAttack_TimeElapsed()
{
	//spawns BlackholeAttack
	SpawnProjectile(BlackHoleProjectileClass);
}


void ASCharacter::Dash()
{
	//Plays AttackAnim
	PlayAnimMontage(AttackAnim);

	//Sets AttackAnim timer
	GetWorldTimerManager().SetTimer(TimerHandle_Dash, this, &ASCharacter::Dash_TimeElapsed, AttackAnimDelay);
}


void ASCharacter::Dash_TimeElapsed()
{
	//spawns DashProjectile
	SpawnProjectile(DashProjectileClass);
}


void ASCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if (ensureAlways(ClassToSpawn))
	{
		//Sets HandLocation
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

		//Sets SpawnParams
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		//Sets Hit Result
		FHitResult Hit;
		FVector TraceStart = CameraComp->GetComponentLocation();
		// endpoint far into the look-at distance (not too far, still adjust somewhat towards crosshair on a miss)
		FVector TraceEnd = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000);

		//Sets shape
		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		//Ignores Player
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		//Sets CollisionObjectQueryParams
		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		//Sets ProjRotation
		FRotator ProjRotation;
		// true if we got to a blocking hit (Alternative: SweepSingleByChannel with ECC_WorldDynamic)
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			// Adjust location to end up at crosshair look-at
			ProjRotation = FRotationMatrix::MakeFromX(Hit.ImpactPoint - HandLocation).Rotator();
		}
		else
		{
			// Fall-back since we failed to find any blocking hit
			ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
		}

		//Sets SpawnTM 
		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
	}
}


void ASCharacter::PrimaryInteract()
{
	//Checks for interact ability
	if (InteractionComp)
	{
		//calls interact 
		InteractionComp->PrimaryInteract();

	}
	
}


