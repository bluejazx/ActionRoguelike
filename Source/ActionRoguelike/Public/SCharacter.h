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
class UParticleSystem;
class USActionComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	/* VisibleAnywhere = read-only, still useful to view in-editor and enforce a convention. */
	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USActionComponent* ActionComp;

	//Function to move along z(forward/back)
	void MoveForward(float Value);

	//Function to move along x(right/left)
	void MoveRight(float Value);

	void SprintStart();

	void SprintStop();

	//Function to begin PrimaryAttack
	void PrimaryAttack();

	//Function to begin BlackHoleAttack
	void BlackHoleAttack();

	//Function to begin Dash
	void Dash();

	//Function to preform interact
	void PrimaryInteract();

	UFUNCTION()
	//Function for OnHealthChanged event
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);
	
	//Function override for binding events
	virtual void PostInitializeComponents() override;

	virtual FVector GetPawnViewLocation() const override;

public:	

	ASCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);
};
