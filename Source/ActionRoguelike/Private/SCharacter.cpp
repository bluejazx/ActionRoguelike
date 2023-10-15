// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SActionComponent.h"


// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates SpringArmComp
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
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComp");

	//Moves in direction this character is facing
	GetCharacterMovement()->bOrientRotationToMovement = true;

	//Allows for RPG(souls-like) camera where player can look into the camera  without changing the direction the player is looking 
	//By rotating to the direction of input
	bUseControllerRotationYaw = false;

	TimeToHitParamName = "TimeToHit";
	
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
}

FVector ASCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
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

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASCharacter::SprintStop);

	//Binds Jump(Space)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

void ASCharacter::HealSelf(float Amount /* = 100 */)
{
	AttributeComp->ApplyHealthChange(this, Amount);
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

void ASCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
}

void ASCharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "Sprint");
}

//Trigger Primary attack Animation then spawn projectile
void ASCharacter::PrimaryAttack()
{
	ActionComp->StartActionByName(this, "PrimaryAttack");
}


void ASCharacter::BlackHoleAttack()
{
	ActionComp->StartActionByName(this, "Blackhole");
}

void ASCharacter::Dash()
{
	ActionComp->StartActionByName(this, "Dash");
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

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
	}

	//Stops input when at 0 or less Health
	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}




