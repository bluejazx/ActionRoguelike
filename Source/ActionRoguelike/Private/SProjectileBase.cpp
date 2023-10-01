// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"


ASProjectileBase::ASProjectileBase()
{
	//Creates a SphereComp
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	//Sets collision profile to Projectile
	SphereComp->SetCollisionProfileName("Projectile");
	//Creates Event when sphere component hits another actor
	SphereComp->OnComponentHit.AddDynamic(this, &ASProjectileBase::OnActorHit);
	//Sets RootComp to SphereComp
	RootComponent = SphereComp;

	//Creates EffectComp
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	//Attaches to SphereComp
	EffectComp->SetupAttachment(RootComponent);

	//Creates MovementComp
	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComp");
	//Makes Velocity follow rotation
	MoveComp->bRotationFollowsVelocity = true;
	//Sets and creates initial values for velocity and gravity
	MoveComp->bInitialVelocityInLocalSpace = true;
	MoveComp->ProjectileGravityScale = 0.0f;
	MoveComp->InitialSpeed = 8000;

}

//Projectile hits other actor Event
void ASProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Triggers explode function
	Explode();
}


//Implementation from it being marked as BlueprintNativeEvent
void ASProjectileBase::Explode_Implementation()
{
	// Check to make sure we aren't already being 'destroyed'
	// Adding ensure to see if we encounter this situation at all
	if (ensure(!IsPendingKill()))
	{
		//Creates explosion effect
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

		//Destroys projectile
		Destroy();
	}
}

void ASProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}