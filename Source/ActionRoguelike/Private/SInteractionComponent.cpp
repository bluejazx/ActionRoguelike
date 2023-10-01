// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGameplayInterface.h"
#include "DrawDebugHelpers.h"



// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	//Creates ObjectQueryParams
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	//Finds Owner
	AActor* MyOwner = GetOwner();



	//Gets Viewpoint
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	//Sets End
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	//For preforming the following trace but with more precision
	//FHitResult Hit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	//Array of Hits
	TArray<FHitResult> Hits;

	//Sets radius
	float Radius = 30.f;

	//makes Sphere
	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	//Finds objects Blocking
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	//makes trace red or green
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		//Check for nullptr
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			//Check for InteractionComp
			if (HitActor->Implements<USGameplayInterface>())
			{
				//cast MyOwner 
				APawn* MyPawn = Cast<APawn>(MyOwner);

				//Executes Interaction
				ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
				//Allows one Interaction
				break;
			}
			
		}

		//draws sphere 
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
	}

	//draws line 
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);


}
