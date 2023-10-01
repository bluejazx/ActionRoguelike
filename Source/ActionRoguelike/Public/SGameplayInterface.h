// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SGameplayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USGameplayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
//The purpose of this interface is to create a share API that allows for things like interacting / looting obejects in the world / level
class ACTIONROGUELIKE_API ISGameplayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	
	//BluePrintNativeEvent Allows for implementation in both Blueprint and C++
	UFUNCTION(BluePrintCallable, BluePrintNativeEvent)
	//Calls Interact
	void Interact(APawn* InstigatorPawn);
};
