// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"


ASExplosiveBarrel::ASExplosiveBarrel()
{
	//Creates MeshComp
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	//Sets physics
	MeshComp->SetSimulatePhysics(true);
	//Sets RootComp to MeshComp
	RootComponent = MeshComp;

	//Creates ForceComp
	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	//Attaches ForceComp
	ForceComp->SetupAttachment(MeshComp);

	// Leaving this on applies small constant force via component 'tick' (Optional)
	ForceComp->SetAutoActivate(false);

	//Sets the Radius and Strength of ForceComp
	ForceComp->Radius = 750.0f;
	ForceComp->ImpulseStrength = 2500.0f; // Alternative: 200000.0 if bImpulseVelChange = false
	// Optional, ignores 'Mass' of other objects (if false, the impulse strength will be much higher to push most objects depending on Mass)
	ForceComp->bImpulseVelChange = true;

	// Optional, default constructor of component already adds 4 object types to affect, excluding WorldDynamic
	//Excludes world dynamic from collisions
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
}


void ASExplosiveBarrel::PostInitializeComponents()
{
	// Don't forget to call parent function
	Super::PostInitializeComponents();

	//Activates ForceComp on hit
	MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);
}


void ASExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Fire impulse on hit 
	ForceComp->FireImpulse();

	// Logging  to make sure we reached the event and provides debug information
	UE_LOG(LogTemp, Log, TEXT("OnActorHit reached (ExplosiveBarrel)"));

	//Logs the name of the actor that hit explosive barrel, and time it was hit
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s,  at fame time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	//Prints a string with all the information form our debug logs
	FString CombinedString = FString::Printf(TEXT("Hit at location %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
}