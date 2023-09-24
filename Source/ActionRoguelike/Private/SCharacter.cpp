// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"


//Where you should  initialize variables and Create/setup components
// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Adds the SpringArmComponent with the name "SpringArmComp" to SCharacter in the editor
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	//Allows  for the camera to follow and update on controller(mouse) vertical inputs
	SpringArmComp->bUsePawnControlRotation = true;
	//Attaches the SpringArmComp to SCharacter Root
	SpringArmComp->SetupAttachment(RootComponent);

	//Adds the CameraComponent with the name "SpringArmComp" to SCharacter in the editor
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	//Attaches the CameraComp to SpringArmComp
	CameraComp->SetupAttachment(SpringArmComp);

	//move the player in the direction SCHracter is facing
	GetCharacterMovement()->bOrientRotationToMovement = true;

	//alllows for RPG(soulslike) camera where player can look into the camera  without changing the direction the player is looking 
	//by rotating to the direction of input
	bUseControllerRotationYaw = false;
}

//Where you want to intialize timers
// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// This is entirely optional, it draws two arrows to visualize rotations of the player
	// -- Rotation Visualization -- //
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	//Starts line at SCharacters location
	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the SCharacters forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw SCharacters Direction inputs
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw Camera Rotation of SCharacters
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);

}


//Binding Inputs
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Allows SCharacter to move along z axis(foward/back using W/S set in editor project settings>Input>axis mappings>MoveForward) using MoveFoward funtion
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	//Allows SCharacter to move along z axis(foward/back using D/A set in editor project settings>Input>axis mappings>MoveRight) using MoveFoward funtion
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	//Allows SCharacter to turn with horizontal controller(mouse) movement
	//Also enbled in blueprint through 'use contorl rotation yaw' in Pawn
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//Allows SCharacter to turn with vertical controller(mouse) movement
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//Sets up the input for PrimaryAttack in ProjectSetting(setting>Input>action mappings>PrimaryAttack>Left Mouse)
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	//Binds Jump to space bar set in (setting>Input>action mappings>Jump>Space
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}


//Movement 

//forward and backwards movement
void ASCharacter::MoveForward(float Value)
{
	//Makes variable of SCharacters control rotation
	FRotator ControlRot = GetControlRotation();
	//Makes sure beforwe using ControlRot.Vector we cant move into the floor(pitch) or sky(Yaw) by setiing there vectors to zero befor taking the input
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	//Says what direction we want to move(We used ControlRot.Vector() which is the direction SCharacter is facing)and Value which is how far(triggered by W=1 or S=-1)
	AddMovementInput(ControlRot.Vector(), Value);
}

//lefta nd right movement
void ASCharacter::MoveRight(float Value)
{
	//Makes variable of SCharacters control rotation
	FRotator ControlRot = GetControlRotation();
	//Makes sure beforwe using ControlRot.Vector we cant move into the floor(pitch) or sky(Yaw) by setiing there vectors to zero befor taking the input
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// X = Forward (Red)
	// Y = Right (Green)
	// Z = Up (Blue)

	//Gets the right axis of the contorller rotator and sets it to the RightVector
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	//Says what direction we want to move(We used RightVector which is the direction right of where SCharacter is facing)and Value which is how far(triggered by D=1 or A=-1)
	AddMovementInput(RightVector, Value);
}


//Actions

//Primary attack
void ASCharacter::PrimaryAttack()
{
	//Gets the hand location of SCharacter
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");


	//assigns SpawnTM to a (rotation and location) we had (where SCharacter is looking and SCharacter's HandLocation)
	FTransform SpawnTM = FTransform(GetActorRotation(), HandLocation);

	//Specifies the rules for spawning the PrimaryAttack(will spawn always)
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//Spawns an actor of ProjectileClass assigned in SCharacter.h as a SubClassOf , then SpawnTM(location,rotation, and scale), SpawnParam(holds optional parameters)
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}


