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

	//the component that will be used for collisions
	UPROPERTY(VisibleAnywhere)
		USphereComponent* SphereComp;

	//Component that is given a velocity and travels in a straight line
	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* MovementComp;

	//Is what is shown in the world for the player 
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* EffectComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
