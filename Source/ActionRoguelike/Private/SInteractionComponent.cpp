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
	//Creates list of Object type's we are checking for with the line trace then Adds WorldDynamic to the list
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	//Finds what Actor this component is attached to
	AActor* MyOwner = GetOwner();



	//Get the viewpoint from attached actor eyes from eye location and rotation for variables
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	//The trace ends in the direction we are facing from Eye location to a distance away
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	//For preforming the following trace but with more precision
	//FHitResult Hit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	//Array for what our sphere trace hits in a sphere
	TArray<FHitResult> Hits;

	//radius of sphere
	float Radius = 30.f;

	//makes our sphere for trace
	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	//Finds objects to interact in a sphere by sweeping from eye location to the end using ObejectQueryParams to find anything that can be interacted with
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	//makes trace red if nothing was hit otherwise if something was hit trace is green
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		//Gets the actor that was hit and validates Hit object to avoid nullptr
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			//make sure the Hit object can be interacted with
			if (HitActor->Implements<USGameplayInterface>())
			{
				//cast MyOwner to a pawn to be passed when executing interact
				APawn* MyPawn = Cast<APawn>(MyOwner);

				//Executes Interaction on hit object Instigated the actor this component is attached to 
				ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
				//added so that characters can only interact with one object at a time
				break;
			}
			
		}

		//draws sphere matching line color
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
	}

	//draws line matching line color
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);


}
