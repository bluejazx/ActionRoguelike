// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrel.generated.h"


class UStaticMeshComponent;
class URadialForceComponent;


UCLASS()
class ACTIONROGUELIKE_API ASExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASExplosiveBarrel();

protected:

	//VisibleAnywhere makes visible in editor
	UPROPERTY(VisibleAnywhere)
	//Physical body
	UStaticMeshComponent* MeshComp;

	//VisibleAnywhere readable in BP
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//ForceComp
	URadialForceComponent* ForceComp;

	virtual void PostInitializeComponents() override;

	// Must be marked with UFUNCTION in order to 'bind' the event
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
