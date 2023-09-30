// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SAttributeComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	//Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates then sets the SphereComp as the root component of the projectile
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	//Sets collision physics to use Projectile profile
	SphereComp->SetCollisionProfileName("Projectile");
	//Sets up an overlap event with some that has health to add damage to that object
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
	//Sets sphere component to root component
	RootComponent = SphereComp;

	//Creates then Attaches the EffectComp to the SphereComp so that they stay in sync
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	//Allows for basic movement of the projectile with and initial speed of 1,000
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Checks for a nullptr
	if (OtherActor)
	{
		//gets the other actor attributes component
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		//checks for a attributeComp on actor isn't null
		if (AttributeComp)
		{
			//changes other actors health by 20
			AttributeComp->ApplyHealthChange(-20.0f);

			//removes SMagicProjectile after damage is applied
			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame

void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
