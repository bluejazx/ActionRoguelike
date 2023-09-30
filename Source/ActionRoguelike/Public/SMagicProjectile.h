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

	//UFUNCTION allows us to bind to this function and trigger our event
	UFUNCTION()
	//this applies damage upon overlap of SMagicProjectile with something that has health
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//VisibleAnywhere makes visible in editor and BlueprintReadOnly makes it readable in BP
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//the physical body component that will be used for collisions
	USphereComponent* SphereComp;

	//VisibleAnywhere makes visible in editor and BlueprintReadOnly makes it readable in BP
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//Component that is given a velocity and travels in a straight line
	UProjectileMovementComponent* MovementComp;

	//VisibleAnywhere makes visible in editor and BlueprintReadOnly makes it readable in BP
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//Is what is shown in the world for the player 
	UParticleSystemComponent* EffectComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
