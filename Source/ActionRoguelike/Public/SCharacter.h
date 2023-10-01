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

	
	//Editable anywhere in attack
	UPROPERTY(EditAnywhere, Category = "Attack")
	//creates a subclass 
	TSubclassOf<AActor> ProjectileClass;

	//Editable anywhere in attack
	UPROPERTY(EditAnywhere, Category = "Attack")
	//creates a subclass 
	TSubclassOf<AActor> BlackHoleProjectileClass;

	//Editable anywhere in attack
	UPROPERTY(EditAnywhere, Category = "Attack")
	//creates a subclass 
	TSubclassOf<AActor> DashProjectileClass;

	//Editable anywhere in attack
	UPROPERTY(EditAnywhere, Category = "Attack")
	//Attack animations
	UAnimMontage* AttackAnim;

	//PrimaryAttack timer
	FTimerHandle TimerHandle_PrimaryAttack;

	//BlackholeAttack Timer
	FTimerHandle TimerHandle_BlackholeAttack;

	//Dash Timer
	FTimerHandle TimerHandle_Dash;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	//Variable for AttackAnimDelay
	float AttackAnimDelay;

	//Visible in editor
	UPROPERTY(VisibleAnywhere)
	//the camera arm
	USpringArmComponent* SpringArmComp;

	//Visible in editor
	UPROPERTY(VisibleAnywhere)
	//the camera following SCharacter
	UCameraComponent * CameraComp;

	//Visible in editor
	UPROPERTY(VisibleAnywhere)
	//Allows SCharacter to interact with object in the world
	USInteractionComponent* InteractionComp;

	//Visible in editor BP readable in components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "components")
	//adds universal attribute class to SCharacter
	USAttributeComponent* AttrributeComp;

	//Function to move along z(forward/back)
	void MoveForward(float Value);

	//Function to move along x(right/left)
	void MoveRight(float Value);

	//Function to begin PrimaryAttack
	void PrimaryAttack();

	//Function to preform Primary Attack
	void PrimaryAttack_TimeElapsed();

	//Function to begin BlackHoleAttack
	void BlackHoleAttack();

	//Function to preform BlackholeAttack_TimeElapsed
	void BlackholeAttack_TimeElapsed();

	//Function to begin Dash
	void Dash();

	//Function to preform Dash_TimeElapsed
	void Dash_TimeElapsed();

	// Re-use spawn logic between attacks
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

	//Function to preform interact
	void PrimaryInteract();

	UFUNCTION()
	//Function for OnHealthChanged event
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);
	
	//Function override for binding events
	virtual void PostInitializeComponents() override;

public:	

	ASCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
