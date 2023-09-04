// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

//Where you should  initialize variables and Create/setup components
// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Adds the SpringArmComponent with the name "SpringArmComp" to SCharacter in the editor
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	//Attaches the SpringArmComp to SCharacter Root
	SpringArmComp->SetupAttachment(RootComponent);

	//Adds the CameraComponent with the name "SpringArmComp" to SCharacter in the editor
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	//Attaches the CameraComp to SpringArmComp
	CameraComp->SetupAttachment(SpringArmComp);
}

//Where you want to intialize timers
// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float Value)
{
	//Says what direction we want to move(We used GetActorForwardVector() which is the direction SCharacter is facing)and Value which is how far(triggered by W=1 or S=-1)
	AddMovementInput(GetActorForwardVector(), Value);
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Allows SCharacter to move along z axis(foward/back using W/S set in editor project settings>Input>axis mappings>MoveForward) using MoveFoward funtion
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);

	//Allows SCharacter to turn with horizontal movement
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

}

