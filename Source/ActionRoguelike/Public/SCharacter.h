// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	//allows for assignment of ProjectileClass assigned in editor SCharacter>ProjectileClass
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	//the camera arm
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	//the camera
	UPROPERTY(VisibleAnywhere)
	UCameraComponent * CameraComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Tells how far from 0 to -1(done with provided Value)to move the player along z axis
	void MoveForward(float Value);

	//Tells how far from 0 to -1(done with provided Value)to move the player along x axis
	void MoveRight(float Value);

	//Triggers the use of Primary Attack
	void PrimaryAttack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
