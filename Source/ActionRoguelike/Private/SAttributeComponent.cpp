// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = 100;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	//Adds the value of delta to health 
	Health += Delta;

	//Broadcast event OnHealthChange to what it concerns
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	//tell us whether this change is successful
	return true;
}


