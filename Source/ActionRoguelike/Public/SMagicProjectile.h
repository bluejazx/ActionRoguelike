// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:

	//VisibleAnywhere makes visdible in editor
	UPROPERTY(VisibleAnywhere)
	//the physical body component that will be used for collisions
	USphereComponent* SphereComp;

	//VisibleAnywhere makes visdible in editor
	UPROPERTY(VisibleAnywhere)
	//Component that is given a velocity and travels in a straight line
	UProjectileMovementComponent* MovementComp;

	//VisibleAnywhere makes visdible in editor
	UPROPERTY(VisibleAnywhere)
	//Is what is shown in the world for the player 
	UParticleSystemComponent* EffectComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
