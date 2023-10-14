// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

//Allows use to use a custom event for when health is changed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static USAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes", meta = (DisplaName = "IsAlive"))
	static bool IsActorAlive(AActor* Actor);

	// Sets default values for this component's properties
	USAttributeComponent();

protected:

	//Edit defaults only makes the variable only editable through BP panel, BlueprintReadOnly makes it readable in BP.
	//category is set to attributes in the details panel
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	//variable for health attribute
	float Health;

	//Edit defaults only makes the variable only editable through BP panel, BlueprintReadOnly makes it readable in BP.
	//category is set to attributes in the details panel
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	//variable for max health attribute
	float HealthMax;

public:	

	//callable in blueprint
	UFUNCTION(BlueprintCallable)
	//constant variable for IsAlive
	bool IsAlive() const;

	//callable in blueprint
	UFUNCTION(BlueprintCallable)
	//bool for is health at max
	bool IsFullHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	//callable in blueprint
	UFUNCTION(BlueprintCallable)
	//gets max health
	float GetHealthMax() const;

	//BlueprintAssignable makes it Assignable in BP
	UPROPERTY(BlueprintAssignable)
	//event for when health has changed
	FOnHealthChanged OnHealthChanged;

	//BlueprintCallable makes it callable in BP
	//category is set in the details panel under attributes
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	//changes health
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

};
