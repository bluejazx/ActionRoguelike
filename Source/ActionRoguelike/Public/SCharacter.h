// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	
	//adds our projectile class to menus in editor under attack category to assign projectiles to
	UPROPERTY(EditAnywhere, Category = "Attack")
	//creates a subclass of actor of ProjectileClass assigned in editor SCharacter>ProjectileClass
	TSubclassOf<AActor> ProjectileClass;

	//adds our Attack animation to menus in editor under attack category to assign attack animations to
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	//Variable for the name for are Primary Attack timer
	FTimerHandle TimerHandle_PrimaryAttack;

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	//VisibleAnywhere makes visible in editor
	UPROPERTY(VisibleAnywhere)
	//the camera arm
	USpringArmComponent* SpringArmComp;

	//VisibleAnywhere makes visible in editor
	UPROPERTY(VisibleAnywhere)
	//the camera following SCharacter
	UCameraComponent * CameraComp;

	//VisibleAnywhere makes visible in editor
	UPROPERTY(VisibleAnywhere)
	//Allows SCharacter to interact with object in the world
	USInteractionComponent* InteractionComp;

	//VisibleAnywhere makes visible in editor, BlueprintReadOnly makes it readable in BP
	//Category set to components in editor details panel
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "components")
	//adds universal attribute class to SCharacter
	USAttributeComponent* AttrributeComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Tells how far from 0 to -1(done with provided Value)to move the player along z axis
	void MoveForward(float Value);

	//Tells how far from 0 to -1(done with provided Value)to move the player along x axis
	void MoveRight(float Value);

	//Triggers the use of Primary Attack
	void PrimaryAttack();

	//Triggers the animation for Primary Attack
	void PrimaryAttack_TimeElapsed();

	//Triggers the use of interact
	void PrimaryInteract();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
