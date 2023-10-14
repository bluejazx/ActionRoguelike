// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SAttributeComponent.h"
#include "SGameplayFunctionLibrary.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	//Sets the size
	SphereComp->SetSphereRadius(20.0f);

	//Sets up an overlap event other actor
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);

	//Sets damage
	DamageAmount = 20.0f;
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Checks for a nullptr and instigator
	if (OtherActor && OtherActor != GetInstigator())
	{
		
		// Apply Damage & Impulse
		if (USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
		{
			// Only explode when we hit something valid
			Explode();
		}
	}
}
