// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = 100;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	//Adds delta to health 
	Health += Delta;

	//Broadcast event OnHealthChange
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	//reports sucess
	return true;
}


