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
	// Sets default values for this component's properties
	USAttributeComponent();

protected:

	//Edit defaults only makes the variable only editable through BP panel, BlueprintReadOnly makes it readable in BP.
	//category is set to attributes in the details panel
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	//variable for health attribute
	float Health;

public:	

	//BlueprintAssignable makes it Assignable in BP
	UPROPERTY(BlueprintAssignable)
	//event for when health has changed
	FOnHealthChanged OnHealthChanged;

	//BlueprintCallable makes it callable in BP
	//category is set in the details panel under attributes
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	//changes health
	bool ApplyHealthChange(float Delta);

};
