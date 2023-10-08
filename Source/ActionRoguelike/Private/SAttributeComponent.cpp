// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"



// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	//Sets HealthMax and Health
	HealthMax = 100;
	Health = HealthMax;
}

bool USAttributeComponent::IsAlive() const
{
	//True while
	return Health > 0.0f;
}

bool USAttributeComponent::IsFullHealth() const
{
	//checks if health is at max
	return Health == HealthMax;
}


float USAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	//Sets old health
	float OldHealth = Health;

	//Sets current health to add delta clamped between 0 and max health
	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	//Subtracts old health form max health to get delta
	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);

	return ActualDelta != 0;
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return FromActor->FindComponentByClass<USAttributeComponent>();
	}

	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	USAttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}

