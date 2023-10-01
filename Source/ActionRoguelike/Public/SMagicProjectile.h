// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SMagicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public ASProjectileBase // Re-parented from AActor
{
	GENERATED_BODY()

protected:

	//Editable in BP in Damage
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	//Variable for DamageAmount
	float DamageAmount;

	
	UFUNCTION()
	//Function on Overlap Event
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:
	// Sets default values
	ASMagicProjectile();


};
